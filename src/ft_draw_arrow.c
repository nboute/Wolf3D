/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:51:49 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 15:52:04 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>

short	ft_getarrowdir(double x, double y, double Ex, double Ey)
{
	int		angle;

	angle = ((int)((atan2(Ex * y - Ey * x, Ex * x + Ey * y)) * 180) / PI);
	if (angle < 0)
		angle += 360;
	return (((angle + 22) / 45) % 8);
}

void	ft_draw_arrow(t_mlx *mlx)
{
	int	***arrow;

	if (mlx->map->id != 1)
		return ;
	arrow = ((t_mazedata*)mlx->mapdata)->arrow;
	if (arrow)
	{
		mlx->arrowdir = ft_getarrowdir(mlx->cam.dirX, mlx->cam.dirY,
			((t_mazedata*)(mlx->mapdata))->exit[0] - mlx->cam.posX,
			((t_mazedata*)mlx->mapdata)->exit[1] - mlx->cam.posY);
		int	i = 0;
		while (i < 64)
		{
			int	j = 0;
			while (j < 64)
			{
				if ((arrow[mlx->arrowdir][i][j] & 0x00FFFFFF) != 0x00FEFEFF)
					ft_place_pixel(arrow[mlx->arrowdir][i][j],
							i + 566, j + 32, mlx);
				j++;
			}
			i++;
		}
	}
}
