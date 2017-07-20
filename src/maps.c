/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 18:34:12 by nboute            #+#    #+#             */
/*   Updated: 2017/07/20 19:05:03 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_map	*ft_start_map(size_t x, size_t y)
{
	t_map	*map;
	size_t	i;
	size_t	j;

	i = 0;
	map = (t_map*)malloc(sizeof(t_map));
	map->map = (char**)malloc(sizeof(char*) * x);
	while (i < x)
	{
		j = 0;
		map->map[i] = (char*)malloc(sizeof(char) * y);
		while (j < y)
		{
			if (i == 0 || i == x - 1 || j == 0 || j == y - 1)
				map->map[i][j] = 1;
			else if (i == x / 2 && j == 1)
				map->map[i][j] = 2;
			else
				map->map[i][j] = 0;
			j++;
		}
		i++;
	}
	map->width = x;
	map->height = y;
	map->startx = (double)x / 2;
	map->starty = (double)y / 2;
	map->id = 0;
	return (map);
}
