/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bx: nboute <marviny42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 18:55:12 bx nboute            #+#    #+#             */
/*   Updated: 2017/07/22 18:58:11 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/header.h"

void	draw_box(t_map *maze, int y, int x)
{
	char	**map;

	map = maze->map;
	int	val;
	val = map[x][y - 1] + map[x - 1][y] * 2 + map[x + 1][y] * 4 + map[x][y + 1] * 8;
	switch(val)
	{
		case 0:
			printf("\x1b[35m%C", 0x2578);
			break ;
		case 1:
			printf("\x1b[35m%C", 0x2579);
			break ;
		case 2:
			printf("\x1b[35m%C", 0x2578);
			break ;
		case 3 :
			printf("\x1b[35m%C", 0x251B);
			break ;
		case 4:
			printf("\x1b[35m%C", 0x257A);
			break ;
		case 5:
			printf("\x1b[35m%C", 0x2517);
			break ;
		case 6:
			printf("\x1b[35m%C", 0x2502);
			break ;
		case 7:
			printf("\x1b[35m%C", 0x253B);
			break ;
		case 8:
			printf("\x1b[35m%C", 0x257B);
			break ;
		case 9:
			printf("\x1b[35m%C", 0x2501);
			break ;
		case 10:
			printf("\x1b[35m%C", 0x2513);
			break ;
		case 11:
			printf("\x1b[35m%C", 0x252B);
			break ;
		case 12:
			printf("\x1b[35m%C", 0x250F);
			break ;
		case 13:
			printf("\x1b[35m%C", 0x2523);
			break ;
		case 14:
			 printf("\x1b[35m%C", 0x2533);
			 break ;
		default:
			printf("\x1b[35m%C", 0x254B);
			break ;
	}
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
			if (mx == x && y == my)
				printf("\x1b[33m%C", 0x2588);
			/*
			else if (maze->map[x][y] == 1)
			{
	if (y - 1 >= 0 && y + 2 <= maze->height && x - 1 >= 0 && x + 2 <= maze->width)
				draw_box(maze, x, y);
	else
			printf("\x1b[35m%C", 0x254B);
			}
			else if (maze->map[x][y] == 3)
				printf("\x1b[31m%C", 0x254B);
			else if (maze->map[x][y] == -1)
				printf("\x1b[31m%C", 0x2574);*/
			else
				printf("%d", maze->map[x][y]);
			x++;
		}
		printf("\n");
	}
	return (0);
}

int		create_maze(t_map *maze, int oldpos, int movey, int movex)
{
	int	dir;
	int	y;
	int	x;

	y = oldpos / maze->width + movey;
	x = oldpos % maze->width + movex;
	maze->map[x - (movex / 2)][y - (movey / 2)] = 0;
	maze->map[x][y] = 0;
	oldpos = x + y * maze->width;
	movey = 0;
	movex = 0;
	while (maze->map[x][y + 2] == 1 || maze->map[x][y - 2] == 1
			|| maze->map[x + 2][y] == 1 || maze->map[x - 2][y] == 1)
	{
		dir = rand() % 4;
		if (dir == 0 && maze->map[x][y + 2] == 1)
			movey = 2;
		else if (dir == 1 && maze->map[x][y - 2] == 1)
			movey = -2;
		else if (dir == 2 && maze->map[x + 2][y] == 1)
			movex = 2;
		else if (dir == 3 && maze->map[x - 2][y] == 1)
			movex = -2;
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
		y = (rnd % 2) * (h_w - out) + 1;
		while (y < h_w && y > out)
		{
			maze[(rnd / 4) * 2 + out][y] = -1;
			y++;
		}
	}
	else
	{
		x = (rnd % 2) * (h_w - out) + 1;
		while (x < h_w && x > out)
		{
			maze[x][(rnd / 4) * 2 + out] = -1;
			x++;
		}
	}
}

#include <locale.h>

t_map	*mazegen(int	size, int out)
{
	int	y;
	int	x;
	t_map *maze;

	setlocale(LC_ALL, "");
	maze = (t_map*)malloc(sizeof(t_map));
	maze->map = (char**)malloc(sizeof(char*) * size);
	srand(time(NULL));
	x = -1;
	maze->height = size;
	maze->width = size;
	while (++x < size)
	{
		maze->map[x] = (char*)malloc(sizeof(char) * size);
		y = -1;
		while (++y < size)
		{
			if (y < out || y > size - out || x < out || x > size - out)
			{
				maze->map[x][y] = 2;
			}
			else
			{
				maze->map[x][y] = 1;
			}
		}
	}
	maze->sprites = (t_sprite*)malloc(sizeof(t_sprite) * 1);
	maze->nbsprites = 1;
	maze->sprites[0].x = 0.0;
	maze->sprites[0].y = 0.0;
	maze->sprites[0].texture = 1;
	print_grid(maze, maze->height, maze->width);
	maze->startx = (size / 2) + (size / 2) % 2;
	maze->starty = maze->startx;
	maze->id = 1;
	create_maze(maze, (int)maze->startx + (int)(maze->starty) * maze->width, 0, 0);
	create_exit(maze->map, size, out);
	return (maze);
}
