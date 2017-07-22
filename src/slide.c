/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bx: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:33:01 bx nboute            #+#    #+#             */
/*   Updated: 2017/07/22 19:49:32 by nboute           ###   ########.fr       */
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
	int		tmp;

	srand(time(NULL));
	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
	{
		ft_putendl("fuckyou");
		exit(-1);
	}
	map->map = (char**)malloc(sizeof(char*) * width);
	if (!map->map)
	{
		ft_putendl("fuckyoutoo");
		exit(-1);
	}
	x = 0;
	while (x < width)
		map->map[x++] = (char*)malloc(sizeof(char) *height);
	walls = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		if (walls > 1)
			walls = rand() % densitx;
		else
			walls ++;
		tmp = 0;
		while (x < width)
		{
			if (y < 5 || y >= height - 5 || x < 5 || x >= width - 5)
				map->map[x][y] = 1;
			else if (y < 10)
				map->map[x][y] = 0;
			else if (!walls)
			{
				if (rand() % densitx == 0)
				{
					tmp = 1;
					map->map[x][y] = 0;
				}
				else
					map->map[x][y] = 1;
			}
			else
				map->map[x][y] = 0;
			x++;
		}
	//	if (!tmp && !walls)
	//		map->map[x][(rand() % (height - 10)) + 5] = 0;
		y++;
	}
	map->nbsprites = 0;
	map->sprites = NULL;
	map->width = width;
	map->height = height;
	map->starty = 7;
	map->startx = 10;
	map->id = 2;
	return (map);
}
