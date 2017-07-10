/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bx: nboute <marviny42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 18:55:12 bx nboute            #+#    #+#             */
/*   Updated: 2017/07/10 21:11:27 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/header.h"

void	draw_box(t_map *maze, int x, int y)
{
	char	**map;

	map = maze->map;
	int	val;

	val = map[x][y - 1] + map[x - 1][y] * 2 + map[x + 1][y] * 4 + map[x][y + 1] * 8;
	if (!val)
		printf("\x1b[35m%C", 0x2588);
	else if (val == 1)
		printf("\x1b[35m%C", 0x2579);
	else if (val == 2)
		printf("\x1b[35m%C", 0x257E);
	else if (val == 3)
		printf("\x1b[35m%C", 0x251B);
	else if (val == 4)
		printf("\x1b[35m%C", 0x257C);
	else if (val == 5)
		printf("\x1b[35m%C", 0x2517);
	else if (val == 6)
		printf("\x1b[35m%C", 0x2503);
	else if (val == 7)
		printf("\x1b[35m%C", 0x253B);
	else if (val == 8)
		printf("\x1b[35m%C", 0x257B);
	else if (val == 9)
		printf("\x1b[35m%C", 0x2501);
	else if (val == 10)
		printf("\x1b[35m%C", 0x2513);
	else if (val == 11)
		printf("\x1b[35m%C", 0x252B);
	else if (val == 12)
		printf("\x1b[35m%C", 0x250F);
	else if (val ==13)
		printf("\x1b[35m%C", 0x2523);
	else if (val == 14)
		printf("\x1b[35m%C", 0x2533);
	else if (val == 15)
		printf("\x1b[35m%C", 0x254B);
}



int		print_grid(t_map *maze, int mx, int my)
{
	int	y;
	int	x;

	y = maze->height;
	while (y)
	{
		y--;
		x = 0;
		while (x < maze->width)
		{
			if (x == mx && y == my)
				printf("\x1b[33m%C", 0x2580);
			else if (maze->map[x][y] == 1)
			{
				draw_box(maze, x, y);
			}
			else if (maze->map[x][y] == 2)
				printf("\x1b[31m%C", 0x2580);
			else
				printf(" ");
			x++;
		}
		printf("\n");
	}
	printf("%d|%d\n", mx, my);
	return (0);
}

int		create_maze(t_map *maze, int oldpos, int movey, int movex)
{
	int	dir;
	int	y;
	int	x;

	y = oldpos % maze->height + movey;
	x = oldpos / maze->width + movex;
	maze->map[y - (movey / 2)][x - (movex / 2)] = 0;
	maze->map[y][x] = 0;
	oldpos = y + x * maze->height;
	movey = 0;
	movex = 0;
	while (maze->map[y][x + 2] == 1 || maze->map[y][x - 2] == 1
			|| maze->map[y + 2][x] == 1 || maze->map[y - 2][x] == 1)
	{
		dir = rand() % 4;
		if (dir == 0 && maze->map[y][x + 2] == 1)
			movex = 2;
		else if (dir == 1 && maze->map[y][x - 2] == 1)
			movex = -2;
		else if (dir == 2 && maze->map[y + 2][x] == 1)
			movey = 2;
		else if (dir == 3 && maze->map[y - 2][x] == 1)
			movey = -2;
		create_maze(maze, oldpos, movey, movex);
	}
	return (0);
}

void	create_exit(char **maze, int h_w, int out)
{
	int	rnd;
	int	y;
	int	x;

	rnd = rand() % ((h_w - out * 2) * 2);
	if (rnd % 4 < 2)
	{
		y = (rnd % 2) * (h_w - out);
		while (y != h_w && y != out)
		{
			maze[y][(rnd / 4) * 2 + out] = 0;
			y++;
		}
	}
	else
	{
		x = (rnd % 2) * (h_w - out);
		while (x != h_w && x != out)
		{
			maze[(rnd / 4) * 2 + 10][x] = 0;
			x++;
		}
	}
}

t_map	*mazegen(t_map *maze, int	size, int out)
{
	int	y;
	int	x;

	srand(time(NULL));
	maze->map = (char **)malloc(sizeof(char*) * size);
	y = -1;
	while (++y < size)
	{
		maze->map[y] = (char*)malloc(sizeof(char) * size);
		x = -1;
		while (++x < size)
		{
			if (y < out || y > size - out || x < out || x > size - out)
				maze->map[y][x] = 2;
			else
				maze->map[y][x] = 1;
		}
	}
	maze->startx = (size / 2) + (size / 2) % 2;
	maze->starty = maze->startx;
	create_maze(maze, maze->startx + maze->starty * size, 0, 0);
	create_exit(maze->map, size, out);
	return (maze);
}
/*

int	main(void)
{
	t_map *maze;

	maze = (t_map*)malloc(sizeof(t_map));
	maze->height = 60;
	maze->width = 60;
	mazegen(maze, maze->height, 4);
	print_grid(maze);
}*/
