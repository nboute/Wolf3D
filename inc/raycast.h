/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:39:08 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 21:02:38 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "../inc/header.h"

typedef struct	s_sprinf
{
	double		sprx;
	double		spry;
	double		invdet;
	double		transfx;
	double		transfy;
	int			sprscreenx;
	int			sprheight;
	int			sprwidth;
	int			sprid;
	int			*sprord;
	double		*sprdist;
}				t_sprinf;

typedef struct	s_flrinf
{
	double		distwall;
	double		distplayer;
	double		currdist;
	double		weight;
	double		currflrx;
	double		currflry;
	int			flrtexx;
	int			flrtexy;
}				t_flrinf;

void			raycast_setparams(t_mlx *mlx, t_vects *v, int x);
void			raycast_dda_alg(t_mlx *mlx, t_vects *v);
void			raycast_calc_wall(t_mlx *mlx, t_vects *v);
void			raycast_calc_floor(t_mlx *mlx, t_vects *v);
void			raycast_calc_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s);
void			raycast_draw_wall(t_mlx *mlx, t_vects *v, int texnum);
void			raycast_draw_floor(t_mlx *mlx, t_vects *v,
			double	floorxwall, double floorywall);
void			raycast_draw_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s,
			t_sprtex *spr);
void			raycast_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s);

#endif
