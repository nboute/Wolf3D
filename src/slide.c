/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bx: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:33:01 bx nboute            #+#    #+#             */
/*   Updated: 2017/08/14 16:48:33 by nboute           ###   ########.fr       */
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
	int		val;

	srand(time(NULL));
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		ft_exit(NULL);
	if (!map)
	{
		ft_putendl("fuckyou");
		exit(-1);
	}
	if (!(map->map = (char**)malloc(sizeof(char*) * width)))
		ft_exit(NULL);
	if (!map->map)
	{
		ft_putendl("fuckyoutoo");
		exit(-1);
	}
	x = 0;
	while (x < width)
		if (!(map->map[x++] = (char*)malloc(sizeof(char) *height)))
			ft_exit(NULL);
	walls = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		if (walls > 3)
			walls = rand() % densitx;
		else
			walls ++;
			val = 0;
		while (x < width)
		{
			if (y < 5 || y >= height - 2 || x < 5 || x >= width - 5)
				map->map[x][y] = 1;
			else if (y < 10)
				map->map[x][y] = 0;
			else if (!walls)
			{
				if (rand() % densitx == 0)
				{
					map->map[x][y] = 0;
					val++;
				}
				else
					map->map[x][y] = 1;
			}
			else
				map->map[x][y] = 0;
			x++;
		}
		if (!val)
			map->map[(rand() % (width - 10)) + 5][y] = 0;
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
