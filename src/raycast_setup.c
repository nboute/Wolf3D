/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:31:02 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:46:46 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include <math.h>

void		raycast_setparams(t_mlx *mlx, t_vects *v, int x)
{
	v->camx = ft_dmap(x, mlx->width, -1, 1);
	v->rayposx = mlx->cam.posx;
	v->rayposy = mlx->cam.posy;
	v->raydirx = mlx->cam.dirx + mlx->cam.planex * v->camx;
	v->raydiry = mlx->cam.diry + mlx->cam.planey * v->camx;
	v->mapx = (int)v->rayposx;
	v->mapy = (int)v->rayposy;
	v->deltadistx = sqrt(1 + (v->raydiry * v->raydiry) /
			(v->raydirx * v->raydirx));
	v->deltadisty = sqrt(1 + (v->raydirx * v->raydirx) /
			(v->raydiry * v->raydiry));
	v->stepx = (v->raydirx < 0) ? -1 : 1;
	v->stepy = (v->raydiry < 0) ? -1 : 1;
	if (v->raydirx < 0)
		v->sidedistx = (v->rayposx - v->mapx) * v->deltadistx;
	else
		v->sidedistx = (v->mapx + 1.0 - v->rayposx) * v->deltadistx;
	if (v->raydiry < 0)
		v->sidedisty = (v->rayposy - v->mapy) * v->deltadisty;
	else
		v->sidedisty = (v->mapy + 1.0 - v->rayposy) * v->deltadisty;
}

void		raycast_dda_alg(t_mlx *mlx, t_vects *v)
{
	while (1)
	{
		if (v->sidedistx < v->sidedisty)
		{
			v->sidedistx += v->deltadistx;
			v->mapx += v->stepx;
			v->side = 0;
		}
		else
		{
			v->sidedisty += v->deltadisty;
			v->mapy += v->stepy;
			v->side = 1;
		}
		if (v->mapx < 0 || v->mapy < 0 || v->mapx > (double)(mlx->map->width
					- 1) || v->mapy > (double)(mlx->map->height - 1))
			break ;
		if (mlx->map->map[v->mapx][v->mapy] >= mlx->map->hit)
			break ;
	}
	if (v->x == mlx->height / 2)
		mlx->cam.target = mlx->map->map[v->mapx][v->mapy];
	v->pwalldt = (v->mapy - v->rayposy + (1 - v->stepy) / 2) / v->raydiry;
	if (v->side == 0)
		v->pwalldt = (v->mapx - v->rayposx + (1 - v->stepx) / 2) / v->raydirx;
}

void		raycast_calc_wall(t_mlx *mlx, t_vects *v)
{
	int	texnum;

	v->lineh = (int)(mlx->height / v->pwalldt);
	v->drawstart = -v->lineh / 2 + mlx->height / 2;
	if (v->drawstart < 0)
		v->drawstart = 0;
	v->drawend = v->lineh / 2 + mlx->height / 2;
	if (v->drawend >= mlx->height)
		v->drawend = mlx->height - 1;
	if (v->drawend >= mlx->height)
		v->drawend = mlx->height - 1;
	if (v->side == 0)
		v->wallx = v->rayposy + v->pwalldt * v->raydiry;
	else
		v->wallx = v->rayposx + v->pwalldt * v->raydirx;
	v->wallx -= floor(v->wallx);
	texnum = 0;
	if (mlx->map->id == 0 || mlx->map->id == 2)
		texnum = (mlx->map->map[v->mapx][v->mapy] - mlx->map->nbfloors)
			% mlx->map->nbwalls;
	raycast_draw_wall(mlx, v, texnum);
}

void		raycast_calc_floor(t_mlx *mlx, t_vects *v)
{
	double	floorxwall;
	double	floorywall;

	if (v->side == 0 && v->raydirx != 0)
	{
		floorxwall = v->mapx + ((v->raydirx > 0) ? 0 : 1.0);
		floorywall = v->mapy + v->wallx;
	}
	else if (v->side == 1 && v->raydiry > 0)
	{
		floorxwall = v->mapx + v->wallx;
		floorywall = v->mapy;
	}
	else
	{
		floorxwall = v->mapx + v->wallx;
		floorywall = v->mapy + 1.0;
	}
	raycast_draw_floor(mlx, v, floorxwall, floorywall);
}

void		raycast_calc_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s)
{
	s->sprx = mlx->map->sprites[s->sprord[s->sprid]].x - mlx->cam.posx;
	s->spry = mlx->map->sprites[s->sprord[s->sprid]].y - mlx->cam.posy;
	if (!s->sprx)
		s->sprx = 0.01;
	if (!s->spry)
		s->spry = 0.01;
	s->invdet = 1.0 / (mlx->cam.planex * mlx->cam.diry
			- mlx->cam.dirx * mlx->cam.planey);
	s->transfx = s->invdet * (mlx->cam.diry * s->sprx
			- mlx->cam.dirx * s->spry);
	s->transfy = s->invdet * (-mlx->cam.planey * s->sprx
			+ mlx->cam.planex * s->spry);
	s->sprscreenx = (int)((mlx->width / 2) * (1 + s->transfx / s->transfy));
	s->sprheight = abs((int)(mlx->height / s->transfy));
	v->drawstarty = ft_imax(-s->sprheight / 2 + mlx->height / 2, 0);
	v->drawendy = ft_imax(ft_imin(s->sprheight / 2 + mlx->height / 2,
				mlx->height - 1), 0);
	s->sprwidth = abs((int)(mlx->width / s->transfy));
	v->drawstartx = ft_imax(-s->sprwidth / 2 + s->sprscreenx, 0);
	v->drawendx =
		ft_imax(ft_imin(s->sprwidth / 2 + s->sprscreenx, mlx->width - 1), 0);
}
