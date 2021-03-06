/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:51:49 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 20:59:17 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>

short	ft_getarrowdir(double x, double y, double ex, double ey)
{
	int	angle;

	angle = ((int)((atan2(ex * y - ey * x, ex * x + ey * y)) * 180) / PI);
	if (angle < 0)
		angle += 360;
	return (((angle + 22) / 45) % 8);
}

void	ft_draw_arrow(t_mlx *mlx)
{
	int	***arrow;
	int	i;
	int	j;

	if (mlx->map->id != 1 || !mlx->mapdata)
		return ;
	arrow = ((t_mazedata*)mlx->mapdata)->arrow;
	if (arrow)
	{
		mlx->arrowdir = ft_getarrowdir(mlx->cam.dirx, mlx->cam.diry,
			((t_mazedata*)(mlx->mapdata))->exit[0] - mlx->cam.posx,
			((t_mazedata*)mlx->mapdata)->exit[1] - mlx->cam.posy);
		i = -1;
		while (++i < 64)
		{
			j = -1;
			while (++j < 64)
				if ((arrow[mlx->arrowdir][i][j] & 0x00FFFFFF) != 0x00FEFEFF)
					ft_place_pixel(arrow[mlx->arrowdir][i][j],
							i + 566, j + 32, mlx);
		}
	}
}

int		***ft_arrow(void)
{
	int	***arrow;

	if (!(arrow = (int***)malloc(sizeof(int**) * 8)))
		ft_exit(NULL);
	arrow[6] = bmp_to_array(TEXTURES"arrow.bmp", 64, 64);
	arrow[7] = bmp_to_array(TEXTURES"arrow_ul.bmp", 64, 64);
	arrow[0] = ft_rotate_2d(arrow[6], 64, 270);
	arrow[1] = ft_rotate_2d(arrow[7], 64, 270);
	arrow[2] = ft_rotate_2d(arrow[6], 64, 180);
	arrow[3] = ft_rotate_2d(arrow[7], 64, 180);
	arrow[4] = ft_rotate_2d(arrow[6], 64, 90);
	arrow[5] = ft_rotate_2d(arrow[7], 64, 90);
	return (arrow);
}
