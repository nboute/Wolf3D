/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:34:45 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 17:57:01 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

void		raycast_draw_wall(t_mlx *mlx, t_vects *v, int texNum)
{
	int	i;
	int	d;
	int	texY;
	int	texX;

	i = v->drawstart;
	texX = 63 - (int)(v->wallX * (double)64);
	i = v->drawstart;
	while (i < v->drawend)
	{
		d = i * 256 - mlx->height * 128 + v->lineH * 128;
		texY = ((d * 64) / v->lineH) / 256;
		if (v->side == 1)
			ft_place_pixel(mlx->map->walls[texNum][texY][texX], v->x, i, mlx);
		else
			ft_place_pixel((mlx->map->walls[texNum][texY][texX] >> 1)
					& 8355711, v->x, i, mlx);
		i++;
	}
}

void		raycast_draw_floor(t_mlx *mlx, t_vects *v,
		double	floorXWall, double floorYWall)
{
	int	i;
	t_flrinf	t;
	int	texNum;

	t.distWall = v->pwalldt;
	t.distPlayer = 0.0;
	if (v->drawend < 0)
		v->drawend = mlx->height;
	i = v->drawend + 1;
	while (i < mlx->height)
	{
		t.currDist = mlx->height / (2.0 * i - mlx->height);
		t.weight = (t.currDist - t.distPlayer) / (t.distWall - t.distPlayer);
		t.currFlrX = t.weight * floorXWall + (1.0 - t.weight) * mlx->cam.posX;
		t.currFlrY = t.weight * floorYWall + (1.0 - t.weight) * mlx->cam.posY;
		t.flrTexX = (int)(t.currFlrX * 64) % 64;
		t.flrTexY = (int)(t.currFlrY * 64) % 64;
		texNum = mlx->map->map[(int)t.currFlrX][(int)t.currFlrY]
			% mlx->map->nbfloors;
		ft_place_pixel(((mlx->map->floors[texNum][t.flrTexY][t.flrTexX] >> 1)
						& 8355711), v->x, i, mlx);
		i++;
	}
}

void		raycast_draw_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s,
		t_sprtex *spr)
{
	int	x;
	int	tex[2];
	int	y;
	int	col;

	x = v->drawstartX - 1;
	while (++x < v->drawendX)
	{
		tex[0] = (int)(256 * (x - (-s->sprWidth / 2 + s->sprscreenX)) * 64
				/ s->sprWidth) / 256;
		if (tex[0] > 0 && s->transfY > 0
				&& x < mlx->width && s->transfY < mlx->zbuff[x])
		{
			y = v->drawstartY - 1;
			while (++y < v->drawendY)
			{
				tex[1] = (((y * 256 - mlx->height * 128 + s->sprHeight * 128)
							* 64) / s->sprHeight) / 256;
				if (tex[1] < 0)
					tex[1] = 0;
				col = spr->text[tex[1]][tex[0]];
				if ((spr->alpha & 0x00FFFFFF) != (col & 0x00FFFFFF))
					ft_place_pixel(col, x, y, mlx);
			}
		}
	}
}

int		raycast_sprites(t_mlx *mlx, t_vects *v)
{
	int			i;
	t_sprinf	s;

	i = -1;
	if (!(s.sprOrd = (int*)malloc(sizeof(int) * mlx->map->nbtextures)))
		ft_exit(NULL);
	if (!(s.sprDist = (double*)malloc(sizeof(double) * mlx->map->nbtextures)))
		ft_exit(NULL);
	while (++i < mlx->map->nbspr)
	{
		s.sprOrd[i] = i;
		s.sprDist[i] = ((mlx->cam.posX - mlx->map->sprites[i].x) *
			(mlx->cam.posX - mlx->map->sprites[i].x) + (mlx->cam.posY -
			mlx->map->sprites[i].y) * (mlx->cam.posY - mlx->map->sprites[i].y));
	}
	if (mlx->map->nbspr > 1)
		ft_combsort(s.sprOrd, s.sprDist, mlx->map->nbspr);
	s.sprid = -1;
	while (++s.sprid < mlx->map->nbspr)
	{
			raycast_calc_sprites(mlx, v, &s);
		if ((s.sprX >= 0.5 || s.sprX <= -0.5)
				|| (s.sprY >= 0.5 || s.sprY <= -0.5))
			raycast_draw_sprites(mlx, v,
					&s, &mlx->map->sprtex[s.sprOrd[s.sprid]]);
	}
	return (1);
}

void		*raycast(void	*data)
{
	t_mlx	*mlx;
	t_vects	*v;
	int		i;

	mlx = ((t_thread*)data)->data;
	i = ((t_thread*)data)->id;
	v = &mlx->vectors[i];
	v->x = (i * mlx->width) / RAYCAST_THREADS;
	i = ((i + 1) * mlx->width) / RAYCAST_THREADS;
	while (v->x < i)
	{
		raycast_setparams(mlx, v, v->x);
		raycast_dda_alg(mlx, v);
		raycast_calc_wall(mlx, v);
		mlx->zbuff[v->x] = v->pwalldt;
		raycast_calc_floor(mlx, v);
		v->x++;
	}
	if (mlx->map->nbspr)
		raycast_sprites(mlx, mlx->vectors);
	return (NULL);
}
