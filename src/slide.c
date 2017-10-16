/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bx: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:33:01 bx nboute            #+#    #+#             */
/*   Updated: 2017/10/16 15:16:39 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../inc/header.h"

t_map	*slidegen(int width, int height, int densitx)
{
	t_map	*map;
	int		y;
	int		x;
	int		walls;
	int		val[2];

	ft_putendl("generating slie map");
	srand(time(NULL));
	if (!(map = new_map()))
		ft_exit(NULL);
	get_map_textures(2, map);
	if (!(map->map = (char**)malloc(sizeof(char*) * width)))
		ft_exit(NULL);
	x = 0;
	while (x < width)
		if (!(map->map[x++] = (char*)malloc(sizeof(char) *height)))
			ft_exit(NULL);
	walls = 0;
	y = 0;
	val[1] = 3;
	while (y < height)
	{
		x = 0;
		if (y > height / 10)
			val[1] = 4;
		if (y > (height * 3) / 10)
			val[1] = 5;
		if (y > (height * 3) / 5)
			val[1] = 6;
		if (walls > val[1] - 1)
			walls = rand() % val[1];
		else
			walls ++;
			val[0] = 0;
		while (x < width)
		{
			if (y < 5 || y >= height - 10 || x < 5 || x >= width - 5)
				map->map[x][y] = val[1] - 2;
			else if (y < 20)
				map->map[x][y] = 0;
			else if (!walls)
			{
				if (rand() % densitx < densitx - densitx / 3 - 1)
				{
					map->map[x][y] = 0;
					val[0]++;
				}
				else
					map->map[x][y] = 1;
			}
			else
				map->map[x][y] = 0;
			x++;
		}
		if (!val[0])
			map->map[(rand() % (width - 10)) + 5][y] = 0;
		y++;
	}
	map->nbspr = 0;
	map->sprites = NULL;
	map->width = width;
	map->height = height;
	map->starty = 7;
	map->startx = 10;
	map->id = 2;
	return (map);
}
