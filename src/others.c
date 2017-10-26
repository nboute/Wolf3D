/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:06:43 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:46:32 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include <stdlib.h>

t_mazedata		*ft_getmazedata(t_mlx *mlx, int i, int j)
{
	char		**map;

	i = 0;
	if (!mlx->mapdata)
	{
		if (!(mlx->mapdata = malloc(sizeof(t_mazedata))))
			ft_exit(NULL);
		((t_mazedata*)mlx->mapdata)->arrow = NULL;
	}
	map = mlx->map->map;
	while (++i < mlx->map->width - 1)
	{
		j = 0;
		while (++j < mlx->map->height - 1)
			if (map[i][j] == 0 && (map[i][j + 1] == 1 || map[i][j - 1] == 1
						|| map[i + 1][j] == 1 || map[i - 1][j] == 1))
			{
				((t_mazedata*)mlx->mapdata)->exit[0] = i;
				((t_mazedata*)mlx->mapdata)->exit[1] = j;
			}
	}
	if (!((t_mazedata*)mlx->mapdata)->arrow)
		((t_mazedata*)mlx->mapdata)->arrow = ft_arrow();
	return ((t_mazedata*)mlx->mapdata);
}

void			ft_combsort(int *order, double *dist, int amount)
{
	int			gap;
	short		swap;
	int			i;

	gap = amount;
	swap = 1;
	while (gap > 1 || swap)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swap = 0;
		i = -1;
		while (++i < amount - gap)
			if (dist[i] < dist[i + gap])
			{
				ft_swap(dist + i, dist + i + gap, sizeof(double));
				ft_swap(order + i, order + i + gap, sizeof(int));
				swap = 0;
			}
	}
}

void			rotate_view(double rotspeed, t_mlx *mlx)
{
	double		tmp;

	tmp = mlx->cam.dirx;
	mlx->cam.dirx = mlx->cam.dirx * cos(rotspeed)
		- mlx->cam.diry * sin(rotspeed);
	mlx->cam.diry = tmp * sin(rotspeed) + mlx->cam.diry * cos(rotspeed);
	tmp = mlx->cam.planex;
	mlx->cam.planex = mlx->cam.planex * cos(rotspeed)
		- mlx->cam.planey * sin(rotspeed);
	mlx->cam.planey = tmp * sin(rotspeed) + mlx->cam.planey * cos(rotspeed);
}
