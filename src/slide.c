/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:33:01 by nboute            #+#    #+#             */
/*   Updated: 2017/07/10 16:54:02 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int		print_grid(char **map, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
/*			if (map[y][x] < 0 || map[y][x] > 2)
				printf("wtf\n");
			if (map[y][x] == 0)
				printf("%d", map[y][x]);
			else if (map[y][x] == 1)
				printf("%d", map[y][x]);
			else
*/				printf("%d", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	return (0);
}

char	**slidegen(int width, int height, int density)
{
	char	**map;
	int		x;
	int		y;
	int		walls;
	int		tmp;

	srand(time(NULL));
	map = (char**)malloc(sizeof(char*) * height);
	y = 0;
	walls = 0;
	while (y < height)
	{
		x = 0;
		if (walls > 1)
			walls = rand() % density;
		else
			walls ++;
		map[y] = (char*)malloc(sizeof(char) * width);
		tmp = 0;
		while (x < width)
		{
			if (x < 5 || x >= width - 5)
				map[y][x] = 2;
			else if (!walls)
			{
				if (rand() % density == 0)
				{
					tmp = 1;
					map[y][x] = 0;
				}
				else
					map[y][x] = 1;
			}
			else
				map[y][x] = 0;
			x++;
		}
		if (!tmp && !walls)
			map[y][(rand() % (width - 10)) + 5] = 0;
		y++;
	}
	return (map);
}
