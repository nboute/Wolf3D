/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:23:20 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:47:45 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/header.h"

void	set_vals(int val[2], int *walls, t_map *map, int y)
{
	val[1] = 3;
	if (y > map->height / 10)
		val[1] = 4;
	if (y > (map->height * 3) / 10)
		val[1] = 5;
	if (y > (map->height * 3) / 5)
		val[1] = 6;
	if (*walls > val[1] - 1)
		*walls = rand() % val[1];
	else
		(*walls)++;
	val[0] = 0;
}

t_map	*create_slide(t_map *map, int val[2], int x, int y)
{
	int	walls;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		set_vals(val, &walls, map, y);
		while (++x < map->width)
		{
			map->map[x][y] = 1;
			if (y < 5 || y >= map->height - 10 || x < 5 || x >= map->width - 5)
				map->map[x][y] = val[1] - 2;
			else if (y < 20 || walls)
				map->map[x][y] = 0;
			else if (!walls)
				if (rand() % 20 < 15)
				{
					map->map[x][y] = 0;
					val[0]++;
				}
		}
		if (!val[0])
			map->map[(rand() % (map->width - 10)) + 5][y] = 0;
	}
	return (map);
}

t_map	*slidegen(int width, int height)
{
	t_map	*map;
	int		x;
	int		val[2];

	srand(time(NULL));
	if (!(map = new_map()))
		ft_exit(NULL);
	map->width = width;
	map->height = height;
	get_map_textures(2, map);
	if (!(map->map = (char**)malloc(sizeof(char*) * width)))
		ft_exit(NULL);
	x = 0;
	while (x < width)
		if (!(map->map[x++] = (char*)malloc(sizeof(char) * height)))
			ft_exit(NULL);
	create_slide(map, val, 0, 0);
	map->nbspr = 0;
	map->sprites = NULL;
	map->starty = 7;
	map->startx = 10;
	map->id = 2;
	return (map);
}
