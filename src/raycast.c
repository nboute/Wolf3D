/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:34:45 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:46:39 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/raycast.h"

void			raycast_draw_wall(t_mlx *mlx, t_vects *v, int texnum)
{
	int			i;
	int			d;
	int			texy;
	int			texx;

	i = v->drawstart;
	texx = 63 - (int)(v->wallx * (double)64);
	i = v->drawstart;
	while (i < v->drawend)
	{
		d = i * 256 - mlx->height * 128 + v->lineh * 128;
		texy = ((d * 64) / v->lineh) / 256;
		if (v->side == 1)
			ft_place_pixel(mlx->map->walls[texnum][texy][texx], v->x, i, mlx);
		else
			ft_place_pixel((mlx->map->walls[texnum][texy][texx] >> 1)
					& 8355711, v->x, i, mlx);
		i++;
	}
}

void			raycast_draw_floor(t_mlx *mlx, t_vects *v,
		double floorxwall, double floorywall)
{
	int			i;
	t_flrinf	t;
	int			texnum;

	t.distwall = v->pwalldt;
	t.distplayer = 0.0;
	if (v->drawend < 0)
		v->drawend = mlx->height;
	i = v->drawend + 1;
	while (i < mlx->height)
	{
		t.currdist = mlx->height / (2.0 * i - mlx->height);
		t.weight = (t.currdist - t.distplayer) / (t.distwall - t.distplayer);
		t.currflrx = t.weight * floorxwall + (1.0 - t.weight) * mlx->cam.posx;
		t.currflry = t.weight * floorywall + (1.0 - t.weight) * mlx->cam.posy;
		t.flrtexx = (int)(t.currflrx * 64) % 64;
		t.flrtexy = (int)(t.currflry * 64) % 64;
		texnum = mlx->map->map[(int)t.currflrx][(int)t.currflry]
			% mlx->map->nbfloors;
		ft_place_pixel(((mlx->map->floors[texnum][t.flrtexy][t.flrtexx] >> 1)
					& 8355711), v->x, i, mlx);
		i++;
	}
}

void			raycast_draw_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s,
		t_sprtex *spr)
{
	int			x;
	int			tex[2];
	int			y;

	x = v->drawstartx - 1;
	while (++x < v->drawendx)
	{
		tex[0] = (int)(256 * (x - (-s->sprwidth / 2 + s->sprscreenx)) * 64
				/ s->sprwidth) / 256;
		if (tex[0] > 0 && s->transfy > 0
				&& x < mlx->width && s->transfy < mlx->zbuff[x])
		{
			y = v->drawstarty - 1;
			while (++y < v->drawendy)
			{
				tex[1] = (((y * 256 - mlx->height * 128 + s->sprheight * 128)
							* 64) / s->sprheight) / 256;
				tex[1] = tex[1] < 0 ? 0 : tex[1];
				if ((spr->alpha & 0x00FFFFFF) !=
						(spr->text[tex[1]][tex[0]] & 0x00FFFFFF))
					ft_place_pixel(spr->text[tex[1]][tex[0]], x, y, mlx);
			}
		}
	}
}

void			order_sprites(t_mlx *mlx, t_sprinf *s)
{
	int	i;

	i = -1;
	if (!(s->sprord = (int*)malloc(sizeof(int) * mlx->map->nbtextures)))
		ft_exit(NULL);
	if (!(s->sprdist = (double*)malloc(sizeof(double) * mlx->map->nbtextures)))
		ft_exit(NULL);
	while (++i < mlx->map->nbspr)
	{
		s->sprord[i] = i;
		s->sprdist[i] = ((mlx->cam.posx - mlx->map->sprites[i].x) *
			(mlx->cam.posx - mlx->map->sprites[i].x) + (mlx->cam.posy -
			mlx->map->sprites[i].y) * (mlx->cam.posy - mlx->map->sprites[i].y));
	}
	ft_combsort(s->sprord, s->sprdist, mlx->map->nbspr);
}

void			raycast_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s)
{
	int			i;

	i = -1;
	order_sprites(mlx, s);
	s->sprid = -1;
	while (++s->sprid < mlx->map->nbspr)
	{
		raycast_calc_sprites(mlx, v, s);
		if ((s->sprx >= 0.5 || s->sprx <= -0.5)
				|| (s->spry >= 0.5 || s->spry <= -0.5))
			raycast_draw_sprites(mlx, v,
					s, &mlx->map->sprtex[s->sprord[s->sprid]]);
	}
}
