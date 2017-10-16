/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:39:08 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 16:43:26 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "../inc/header.h"

typedef struct	s_sprinf
{
	double		sprX;
	double		sprY;
	double		invDet;
	double		transfX;
	double		transfY;
	int			sprscreenX;
	int			sprHeight;
	int			sprWidth;
	int			sprid;
	int			*sprOrd;
	double		*sprDist;
}				t_sprinf;

typedef struct	s_flrinf
{
	double		distWall;
	double		distPlayer;
	double		currDist;
	double		weight;
	double		currFlrX;
	double		currFlrY;
	int			flrTexX;
	int			flrTexY;
}				t_flrinf;


void		raycast_setparams(t_mlx *mlx, t_vects *v, int	x);
void		raycast_dda_alg(t_mlx *mlx, t_vects *v);
void		raycast_calc_wall(t_mlx *mlx, t_vects *v);
void		raycast_calc_floor(t_mlx *mlx, t_vects *v);
void		raycast_calc_sprites(t_mlx * mlx, t_vects *v, t_sprinf *s);
void		raycast_draw_wall(t_mlx *mlx, t_vects *v, int texNum);
void		raycast_draw_floor(t_mlx *mlx, t_vects *v,
		double	floorXWall, double floorYWall);
void		raycast_draw_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s,
		t_sprtex *spr);
int		raycast_sprites(t_mlx *mlx, t_vects *v);

#endif
