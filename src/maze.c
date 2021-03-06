/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:08:16 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 15:41:14 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "../inc/header.h"
#include "../inc/bitmap.h"

void		try_path(int pos, t_map *maze, int dir)
{
	int	movex;
	int	movey;
	int	y;
	int	x;

	y = pos / maze->width;
	x = pos % maze->width;
	movex = 0;
	movey = 0;
	while (maze->map[x][y + 2] == 2 || maze->map[x][y - 2] == 2
			|| maze->map[x + 2][y] == 2 || maze->map[x - 2][y] == 2)
	{
		dir = rand() % 4;
		if (dir == 0 && maze->map[x][y + 2] == 2)
			movey = 2;
		else if (dir == 1 && maze->map[x][y - 2] == 2)
			movey = -2;
		else if (dir == 2 && maze->map[x + 2][y] == 2)
			movex = 2;
		else if (dir == 3 && maze->map[x - 2][y] == 2)
			movex = -2;
		if (movex || movey)
			create_maze(maze, pos, movey, movex);
	}
}

void		create_maze(t_map *maze, int oldpos, int movey, int movex)
{
	int	x;
	int	y;

	y = oldpos / maze->width + movey;
	x = oldpos % maze->width + movex;
	maze->map[x - (movex / 2)][y - (movey / 2)] = 0;
	maze->map[x][y] = 0;
	oldpos = x + y * maze->width;
	try_path(oldpos, maze, 0);
}

void		create_exit(char **maze, int h_w, int out, int rnd)
{
	int	y;
	int	x;
	int	exit;

	exit = 0;
	while (!exit)
	{
		rnd = rand() % ((h_w - out * 2) * 2);
		if (rnd % 4 < 2)
		{
			y = (h_w - out) + 1;
			if (y < h_w - 1)
				exit = 1;
			while (y < h_w - 1)
				maze[(rnd / 4) * 2 + out][y++] = 1;
		}
		else
		{
			x = (h_w - out) + 1;
			if (x < h_w - 1)
				exit = 1;
			while (x < h_w - 1)
				maze[x++][(rnd / 4) * 2 + out] = 1;
		}
	}
}

t_map		*mazegen_p2(int size, int out, t_map *maze)
{
	int	x;
	int	y;

	x = -1;
	while (++x < size)
	{
		if (!(maze->map[x] = (char*)malloc(sizeof(char) * size)))
			ft_exit(NULL);
		y = -1;
		while (++y < size)
		{
			if (y < out || y > size - out || x < out || x > size - out)
				maze->map[x][y] = maze->nbfloors + 1;
			else
				maze->map[x][y] = maze->nbfloors;
		}
	}
	maze->startx = (size / 2) + (size / 2) % 2;
	maze->starty = maze->startx;
	maze->id = 1;
	return (maze);
}

t_map		*mazegen(int size, int out)
{
	t_map *maze;

	setlocale(LC_ALL, "");
	if (!(maze = new_map()))
		ft_exit(NULL);
	if (!(maze->map = (char**)malloc(sizeof(char*) * size)))
		ft_exit(NULL);
	get_map_textures(1, maze);
	srand(time(NULL));
	maze->height = size;
	maze->width = size;
	maze->hit = maze->nbfloors;
	mazegen_p2(size, out, maze);
	create_maze(maze,
			(int)maze->startx + (int)(maze->starty) * maze->width, 0, 0);
	create_exit(maze->map, size, out, 0);
	return (maze);
}
