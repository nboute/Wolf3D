/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:31:02 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 16:42:06 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"
#include <math.h>

void		raycast_setparams(t_mlx *mlx, t_vects *v, int	x)
{
	v->camX = ft_dmap(x, mlx->width, -1, 1);
	v->rayposX = mlx->cam.posX;
	v->rayposY = mlx->cam.posY;
	v->raydirX = mlx->cam.dirX + mlx->cam.planeX * v->camX;
	v->raydirY = mlx->cam.dirY + mlx->cam.planeY * v->camX;
	v->mapX = (int)v->rayposX;
	v->mapY = (int)v->rayposY;
	v->deltadistX = sqrt(1 + (v->raydirY * v->raydirY) /
			(v->raydirX * v->raydirX));
	v->deltadistY = sqrt(1 + (v->raydirX * v->raydirX) /
			(v->raydirY * v->raydirY));
	v->stepX = (v->raydirX < 0) ? -1 : 1;
	v->stepY = (v->raydirY < 0) ? -1 : 1;
	if (v->raydirX < 0)
		v->sidedistX = (v->rayposX - v->mapX) * v->deltadistX;
	else
		v->sidedistX = (v->mapX + 1.0 - v->rayposX) * v->deltadistX;
	if (v->raydirY < 0)
		v->sidedistY = (v->rayposY - v->mapY) * v->deltadistY;
	else
		v->sidedistY = (v->mapY + 1.0 - v->rayposY) * v->deltadistY;
}

void		raycast_dda_alg(t_mlx *mlx, t_vects *v)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (v->sidedistX < v->sidedistY)
		{
			v->sidedistX += v->deltadistX;
			v->mapX += v->stepX;
			v->side = 0;
		}
		else
		{
			v->sidedistY += v->deltadistY;
			v->mapY += v->stepY;
			v->side = 1;
		}
		if (mlx->map->map[v->mapX][v->mapY] >= mlx->map->hit)
			hit = 1;
	}
	if (v->x == mlx->height / 2)
		mlx->cam.target = mlx->map->map[v->mapX][v->mapY];
	if (v->side == 0)
		v->pwalldt = (v->mapX - v->rayposX + (1 - v->stepX) / 2) / v->raydirX;
	else
		v->pwalldt = (v->mapY - v->rayposY + (1 - v->stepY) / 2) / v->raydirY;
}

void		raycast_calc_wall(t_mlx *mlx, t_vects *v)
{
	int	texNum;
	v->lineH = (int)(mlx->height / v->pwalldt);
	v->drawstart = -v->lineH / 2 + mlx->height / 2;
	if (v->drawstart < 0)
		v->drawstart = 0;
	v->drawend = v->lineH / 2 + mlx->height / 2;
	if (v->drawend >= mlx->height)
		v->drawend = mlx->height - 1;
	if (v->drawend >= mlx->height)
		v->drawend = mlx->height - 1;
	if (v->side == 0)
		v->wallX = v->rayposY + v->pwalldt * v->raydirY;
	else
		v->wallX = v->rayposX + v->pwalldt * v->raydirX;
	v->wallX -= floor(v->wallX);
	texNum = 0;
	if (mlx->map->id == 0 || mlx->map->id == 2)
		texNum = (mlx->map->map[v->mapX][v->mapY] - mlx->map->nbfloors)
			% mlx->map->nbwalls;
	raycast_draw_wall(mlx, v, texNum);
}

void		raycast_calc_floor(t_mlx *mlx, t_vects *v)
{
	double	floorXWall;
	double	floorYWall;
	if (v->side == 0 && v->raydirX != 0)
	{
		floorXWall = v->mapX + ((v->raydirX > 0) ? 0 : 1.0);
		floorYWall = v->mapY + v->wallX;
	}
	else if (v->side == 1 && v->raydirY > 0)
	{
		floorXWall = v->mapX + v->wallX;
		floorYWall = v->mapY;
	}
	else
	{
		floorXWall = v->mapX + v->wallX;
		floorYWall = v->mapY + 1.0;
	}
	raycast_draw_floor(mlx, v, floorXWall, floorYWall);
}

void		raycast_calc_sprites(t_mlx * mlx, t_vects *v, t_sprinf *s)
{
	s->sprX = mlx->map->sprites[s->sprOrd[s->sprid]].x - mlx->cam.posX;
	s->sprY = mlx->map->sprites[s->sprOrd[s->sprid]].y - mlx->cam.posY;
	if (s->sprX == 0)
		s->sprX = 0.01;
	if (s->sprY == 0)
		s->sprY = 0.01;
	s->invDet = 1.0 / (mlx->cam.planeX * mlx->cam.dirY
			- mlx->cam.dirX * mlx->cam.planeY);
	s->transfX = s->invDet * (mlx->cam.dirY * s->sprX
			- mlx->cam.dirX * s->sprY);
	s->transfY = s->invDet * (-mlx->cam.planeY * s->sprX
			+ mlx->cam.planeX * s->sprY);
	s->sprscreenX = (int)((mlx->width / 2) * (1 + s->transfX / s->transfY));
	s->sprHeight = abs((int)(mlx->height / s->transfY));
	v->drawstartY = -s->sprHeight / 2 + mlx->height / 2;
	if (v->drawstartY < 0)
		v->drawstartY = 0;
	v->drawendY = s->sprHeight / 2 + mlx->height / 2;
	if (v->drawendY >= mlx->height)
		v->drawendY = mlx->height - 1;
	if (v->drawendY < 0)
		v->drawendY = 0;
	s->sprWidth = abs((int)(mlx->width / s->transfY));
	v->drawstartX = -s->sprWidth / 2 + s->sprscreenX;
	if (v->drawstartX < 0)
		v->drawstartX = 0;
	v->drawendX = s->sprWidth / 2 + s->sprscreenX;
	if (v->drawendX >= mlx->width)
		v->drawendX = mlx->width - 1;
	if (v->drawendX < 0)
		v->drawendX = 0;
}
