/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bx: nboute <marviny42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 18:55:12 bx nboute            #+#    #+#             */
/*   Updated: 2017/08/23 19:55:54 by nboute           ###   ########.fr       */
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

int		***ft_arrow(void)
{
	int	***arrow;

	if (!(arrow = (int***)malloc(sizeof(int**) * 8)))
		ft_exit(NULL);
	arrow[0] = bmp_to_array(TEXT_PATH"arrow.bmp", 64, 64);
	arrow[1] = bmp_to_array(TEXT_PATH"arrow_ul.bmp", 64, 64);
	ft_putendl("l");
	arrow[2] = ft_rotate_2d(arrow[0], 64, 270);
	ft_putendl("dl");
	arrow[3] = ft_rotate_2d(arrow[1], 64, 270);
	ft_putendl("d");
	arrow[4] = ft_rotate_2d(arrow[0], 64, 180);
	ft_putendl("dr");
	arrow[5] = ft_rotate_2d(arrow[1], 64, 180);
	ft_putendl("r");
	arrow[6] = ft_rotate_2d(arrow[0], 64, 90);
	ft_putendl("ur");
	arrow[7] = ft_rotate_2d(arrow[1], 64, 90);
	return (arrow);
}

t_mazedata	*ft_getmazedata(t_mlx *mlx)
{
	int		i;
	int		j;
	char	**map;
	t_mazedata	*data;

	i = 1;
	ft_putchar('a');
	if (!(data = malloc(sizeof(t_mazedata))))
		ft_exit(NULL);
	map = mlx->map->map;
	while (i < mlx->map->width - 1)
	{
		j = 1;
		while (j < mlx->map->height - 1)
		{
			if (map[i][j] == 0 && (map[i][j + 1] == -1 || map[i][j - 1] == -1
						|| map[i + 1][j] == -1 || map[i - 1][j] == -1))
			{
				data->exit[0] = i;
				data->exit[1] = j;
			}
			j++;
		}
		i++;
	}
	ft_putchar('b');
	data->arrow = ft_arrow();
	ft_putchar('c');
	return (data);
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
	int	exit;

	exit = 0;
	while (!exit)
	{
		rnd = rand() % ((h_w - out * 2) * 2);
		if (rnd % 4 < 2)
		{
			y = (h_w - out) + 1;
			while (y < h_w - 1)
			{
				exit = 1;
				maze[(rnd / 4) * 2 + out][y] = -1;
				y++;
			}
		}
		else
		{
			x = (h_w - out) + 1;
			while (x < h_w - 1)
			{
				exit = 1;
				maze[x][(rnd / 4) * 2 + out] = -1;
				x++;
			}
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
	if (!(maze = (t_map*)malloc(sizeof(t_map))))
		ft_exit(NULL);
	if (!(maze->map = (char**)malloc(sizeof(char*) * size)))
		ft_exit(NULL);
	srand(time(NULL));
	x = -1;
	maze->height = size;
	maze->width = size;
	while (++x < size)
	{
		if (!(maze->map[x] = (char*)malloc(sizeof(char) * size)))
			ft_exit(NULL);
	printf("|||%p|%d||||\n", maze->map[x], x);
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
	if (!(maze->sprites = (t_sprite*)malloc(sizeof(t_sprite) * 1)))
		ft_exit(NULL);
	maze->nbsprites = 1;
	printf("%p||||\n", maze->map);
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
