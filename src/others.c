/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:06:43 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 19:06:03 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_mazedata	*ft_getmazedata(t_mlx *mlx)
{
	int			i;
	int			j;
	char		**map;
	t_mazedata	*data;

	i = 0;
	if (!(data = malloc(sizeof(t_mazedata))))
		ft_exit(NULL);
	map = mlx->map->map;
	while (++i < mlx->map->width - 1)
	{
		j = 0;
		while (++j < mlx->map->height - 1)
			if (map[i][j] == 0 && (map[i][j + 1] == 1 || map[i][j - 1] == 1
						|| map[i + 1][j] == 1 || map[i - 1][j] == 1))
			{
				data->exit[0] = i;
				data->exit[1] = j;
			}
	}
	data->hp = 100;
	data->arrow = ft_arrow();
	return (data);
}

void		ft_combsort(int *order, double *dist, int amount)
{
	int		gap;
	short	swap;
	int		i;

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