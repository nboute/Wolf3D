/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_basics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:52:16 by nboute            #+#    #+#             */
/*   Updated: 2017/07/11 19:10:54 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

void			ft_place_pixel(int color, int x, int y, t_mlx *mlx)
{
	*(unsigned*)(mlx->data + x * mlx->bpx / 8 + y * mlx->size) = color;
}

int		***gen_text(void)
{
	int	x;
	int	y;
	int	***textures;
	int	i;

	textures = (int***)malloc(sizeof(int**) * 14);
		x = 0;
	i = 0;
	while (i < 8)
	{
		textures[i] = (int**)malloc(sizeof(int*) * 64);
		x = 0;
		while (x < 64)
		{
			y = 0;
			textures[i][x] = (int*)malloc(sizeof(int) * 64);
			while (y < 64)
			{
				int	xorcolor = (x * 256 / 64) ^ (y * 256 / 64);
				int	ycolor = y * 256 / 64;
				int	xycolor = y * 128 / 64 + x * 128 / 64;
				if (i == 0)
					textures[i][x][y] = 65536 * 254 * (x != y && x != 64 - y);
				else if (i == 1)
					textures[i][x][y] = xycolor + 256 * xycolor + 65536 * xycolor;
				else if (i == 2)
					textures[i][x][y] = 256 * xycolor + 65536 * xycolor;
				else if (i == 3)
					textures[i][x][y] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
				else if (i == 4)
					textures[i][x][y] = 256 * xorcolor;
				else if (i == 5)
					textures[i][x][y] = 65536 * 192 * (x % 16 && y % 16);
				else if (i == 6)
					textures[i][x][y] = 65536 * ycolor;
				else if (i == 7)
					textures[i][x][y] = 128 + 256 * 128 + 65536 * 128;
				else
					textures[i][x][y] = 65536 * (i - 8) * 32 + 256 * x * 4 + y * 4;
				y++;
			}
			x++;
		}
		i++;
	}
	ft_putstr("textures loaded\n");
	return (textures);
}

int		print_keys(void *ptr)
{
	t_mlx *mlx;

	mlx = (t_mlx*)ptr;
//	printf("       UP: %d\nLEFT:%d    RIGHT:%d\n        DOWN:%d\n", mlx->keys[0].pressed, mlx->keys[2].pressed, mlx->keys[3].pressed, mlx->keys[1].pressed);
	return (0);
}

int		key_released(int key, void *ptr)
{
	t_mlx *mlx;
	int	i;

	i = 0;
	mlx = (t_mlx*)ptr;
	while (i < 4)
	{
		if (mlx->keys[i].key == key)
		{
			mlx->keys[i].pressed = 0;
			return (0);
		}
		i++;
	}
	ptr = NULL;
	return (0);
}

int		key_pressed(int key, void *ptr)
{
	t_mlx *mlx;
	t_keys *k;
	int	i;

	i = 0;
	mlx = (t_mlx*)ptr;
	k = mlx->keys;
	if (key >= KEY_LEFT || key <= KEY_UP)
		while (i < 4)
		{
			if (k[i].key == key)
			{
				if (!k[i].pressed)
				{
					k[i].pressed = 1;
					return (0);
				}
				else
					return (0);
			}
			i++;
		}
	if (key == 46)
	{
		system("clear");
		print_grid(mlx->map, (int)mlx->vectors->posX, (int)mlx->vectors->posY);
	}
	else if (key == 14)
	{
		int	x, y;
		x = 0;
		while (x < mlx->map->width && mlx->map->map[x][y] != 3)
		{
			y = 0;
			while (y < mlx->map->height && mlx->map->map[x][y] != 3)
			{
			y++;
			}
			x++;
		}
		mlx->vectors->posX = x + 0.5;
		mlx->vectors->posY = y + 0.5;
	}
	return (0);
}

void	rotate_view(double rotspeed, t_vects *v)
{
	double	tmp;

	tmp = v->dirX;
	v->dirX = v->dirX * cos(rotspeed) - v->dirY * sin(rotspeed);
	v->dirY = tmp * sin(rotspeed) + v->dirY * cos(rotspeed);
	tmp = v->planeX;
	v->planeX = v->planeX * cos(rotspeed) - v->planeY * sin(rotspeed);
	v->planeY = tmp * sin(rotspeed) + v->planeY * cos(rotspeed);
}

void	ft_move(t_mlx *mlx)
{
	t_vects	*v;
	t_keys	*k;
	double	val[2];

	v = mlx->vectors;
	k = mlx->keys;
	val[0] = v->dirX * mlx->movespeed;
	val[1] = v->dirY * mlx->movespeed;
	if (k[0].pressed && !k[1].pressed)
	{
		if (v->posX + val[0] >= 0 && (int)(v->posX + val[0]) < mlx->map->width)
			if (mlx->map->map[(int)(v->posX + val[0])][(int)v->posY] == 0 || mlx->map->map[(int)(v->posX + val[0])][(int)v->posY] == 3)
				v->posX += val[0];
		if (v->posY + val[1] >= 0 && (int)(v->posY + val[1]) < mlx->map->width)
			if (mlx->map->map[(int)v->posX][(int)(v->posY + val[1])] == 0)
				v->posY += val[1];
	}
	if (k[1].pressed && !k[0].pressed)
	{
		if (v->posX - val[0] >= 0 && (int)(v->posX - val[0]) < mlx->map->width)
			if (mlx->map->map[(int)(v->posX - val[0])][(int)v->posY] == 0 || mlx->map->map[(int)(v->posX + val[0])][(int)v->posY] == 3)
				v->posX -= val[0];
		if (v->posY - val[1] >= 0 && (int)(v->posY - val[1]) < mlx->map->height)
			if (mlx->map->map[(int)v->posX][(int)(v->posY - val[1])] == 0)
				v->posY -= val[1];
	}
	if (k[2].pressed && !k[3].pressed)
	{
		rotate_view(mlx->rotspeed, v);
	}
	if (k[3].pressed && !k[2].pressed)
	{
		rotate_view(-mlx->rotspeed, v);
	}
}

int		raycast(t_mlx *mlx)
{
	t_vects	*v;

	v = mlx->vectors;
	int	x = 0;
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpx, &mlx->size, &mlx->endian);
	while (x < mlx->width)
	{
		v->camX = ft_dmap(x, mlx->width, -1, 1);
		v->rayposX = v->posX;
		v->rayposY = v->posY;
		v->raydirX = v->dirX + v->planeX * v->camX;
		v->raydirY = v->dirY + v->planeY * v->camX;
		v->mapX = (int)v->rayposX;
		v->mapY = (int)v->rayposY;
		v->deltadistX = sqrt(1 + (v->raydirY * v->raydirY) / (v->raydirX * v->raydirX));
		v->deltadistY = sqrt(1 + (v->raydirX * v->raydirX) / (v->raydirY * v->raydirY));
		int	hit = 0;
		int	side;
		if (v->raydirX < 0)
		{
			v->stepX = -1;
			v->sidedistX = (v->rayposX - v->mapX) * v->deltadistX;
		}
		else
		{
			v->stepX = 1;
			v->sidedistX = (v->mapX + 1.0 - v->rayposX) * v->deltadistX;
		}
		if (v->raydirY < 0)
		{
			v->stepY = -1;
			v->sidedistY = (v->rayposY - v->mapY) * v->deltadistY;
		}
		else
		{
			v->stepY = 1;
			v->sidedistY = (v->mapY + 1.0 - v->rayposY) * v->deltadistY;
		}
		while (!hit)
		{
			if (v->sidedistX < v->sidedistY)
			{
				v->sidedistX += v->deltadistX;
				v->mapX += v->stepX;
				side = 0;
			}
			else
			{
				v->sidedistY += v->deltadistY;
				v->mapY += v->stepY;
				side = 1;
			}
			if (mlx->map->map[v->mapX][v->mapY] && mlx->map->map[v->mapX][v->mapY] != 3)
				hit = 1;
		}
		if (side == 0)
			v->perpwalldist = (v->mapX - v->rayposX + (1 - v->stepX) / 2) / v->raydirX;
		else
			v->perpwalldist = (v->mapY - v->rayposY + (1 - v->stepY) / 2) / v->raydirY;
		int	lineH = (int)(mlx->height / v->perpwalldist);
		int	drawstart = -lineH / 2 + mlx->height / 2;
		if (drawstart < 0)
			drawstart = 0;
		int	drawend = lineH / 2 + mlx->height / 2;
		if (drawend >= mlx->height)
			drawend = mlx->height - 1;
		if (drawend >= mlx->height)
			drawend = mlx->height - 1;
		double	wallX;
		int texNum;
		if (side == 0)
		{
			texNum = 0 + 2 * (v->raydirX > 0);
			wallX = v->rayposY + v->perpwalldist * v->raydirY;
		}
		else
		{
			texNum = 1 + 2 * (v->raydirY > 0);
			wallX = v->rayposX + v->perpwalldist * v->raydirX;
		}
		wallX -= floor(wallX);
		int	texX;
		texX = (int)(wallX * (double)64);
		texX = 64 - texX - 1;
		int	color;
	/*
	if (mlx->map->map[v->mapX][v->mapY])
	{
		val = 1;
	}
	else if (mlx->map->map[v->mapX][v->mapY] == 1)
	{
		val = 2;
	}
	else if (mlx->map->map[v->mapX][v->mapY] == 2)
	{
		val = 3;
	}
	else if (mlx->map->map[v->mapX][v->mapY] == 3)
	{
		val = 4;
	}
		switch (val)
		{
			case 0 : color = 0x00FFFF00;
					 break;
			case 1 : color = 0x000000FF;
					 break;
			case 2 : color = 0x0000FF00;
					 break;
			case 3 : color = 0x00FF0000;
					 break;
			default : color = 0x0000FFFF;
					  break;
		}*/
		int	i;
			i = drawstart;
			while (i < drawend)
			{
				int	d = i * 256 - mlx->height * 128 + lineH * 128;
				int	texY = ((d * 64) / lineH) / 256;
				color = mlx->textures[texNum][texX][texY];
				if (side == 1)
					color = (color >> 1) & 8355711;
				ft_place_pixel(color, x, i, mlx);
				i++;
			}
			double floorXWall, floorYWall;
			if (side == 0 && v->raydirX > 0)
			{
				floorXWall = v->mapX;
				floorYWall = v->mapY + wallX;
			}
			else if (side == 0 && v->raydirX < 0)
			{
				floorXWall = v->mapX + 1.0;
				floorYWall = v->mapY + wallX;
			}
			else if (side == 1 && v->raydirY > 0)
			{
				floorXWall = v->mapX + wallX;
				floorYWall = v->mapY;
			}
			else
			{
				floorXWall = v->mapX + wallX;
				floorYWall = v->mapY + 1.0;
			}
			double distWall, distPlayer, currentDist;
			distWall = v->perpwalldist;
			distPlayer = 0.0;
			if (drawend < 0)
				drawend = mlx->height;
			i = drawend + 1;
			while (i < mlx->height)
			{
			currentDist = mlx->height / (2.0 * i - mlx->height);
			double	weight = (currentDist - distPlayer) / (distWall - distPlayer);
			double	currentfloorX = weight * floorXWall + (1.0 - weight) * v->posX;
			double	currentfloorY = weight * floorYWall + (1.0 - weight) * v->posY;
			int	floortexX, floortexY;
			floortexX = (int)(currentfloorX * 64) % 64;
			floortexY = (int)(currentfloorY * 64) % 64;
			ft_place_pixel(((mlx->textures[3][floortexX][floortexY] >> 1) & 8355711), x, i, mlx);
				i++;
			}
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	loop(void *ptr)
{
	t_mlx *mlx;

	mlx = (t_mlx*)ptr;
	printf("%p\n", mlx->win);
	ft_move(mlx);
	raycast(mlx);
	return (0);
}
#include <locale.h>
#include <stdio.h>

int	main(void)
{
	t_mlx mlx;

	t_map maze;

	setlocale(LC_ALL, "");
	maze.height = 64;
	maze.width = 64;
	mazegen(&maze, maze.height, 4);
	mlx.map = &maze;
	mlx.textures = gen_text();
/*	mlx.map->maphei = 64;
	mlx.map->mapwid = 64;
	if (!(mlx.map->map = (char**)malloc(sizeof(char*) * (mlx.map->maphei + 1))))
		return (-1);
*/	if (!(mlx.vectors = (t_vects*)malloc(sizeof(t_vects))))
		return (-1);
	mlx.vectors->posX = mlx.map->startx + 0.5;
	mlx.vectors->posY = mlx.map->starty + 0.5;
	mlx.vectors->dirX = -1;
	mlx.vectors->dirY = 0;
	mlx.vectors->planeX = 0;
	mlx.vectors->planeY = 0.66;
	if (!(mlx.keys = (t_keys*)malloc(sizeof(t_keys) * 4)))
		return (-1);
	mlx.keys[0].key = KEY_UP;
	mlx.keys[1].key = KEY_DOWN;
	mlx.keys[2].key = KEY_LEFT;
	mlx.keys[3].key = KEY_RIGHT;
	mlx.keys[0].pressed = 0;
	mlx.keys[1].pressed = 0;
	mlx.keys[2].pressed = 0;
	mlx.keys[3].pressed = 0;
	mlx.height = 1000;
	mlx.width = 1000;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.height, mlx.width, "Wolf3D");
	mlx.img = NULL;
/*	int	y;
	int	x = 0;
	while (x < mlx.map->mapwid)
	{
		y = 0;
		mlx.map->map[x] = (char*)malloc(sizeof(char) * (mlx.map->maphei + 1));
		while (y < mlx.map->maphei)
		{
			if ((x == 0 || x == 63 || y == 0 || y == 63) || (x == 30 && y > 20 && y < 50 && y != 32))
				mlx.map->map[x][y] = 1;
			else
				mlx.map->map[x][y] = 0;
			y++;
		}
		mlx.map->map[x][y] = '\0';
		x++;
	}*/
	mlx.movespeed = 0.05;
	mlx.rotspeed = 0.05;
//	mlx.map->map[x] = NULL;
	mlx_hook(mlx.win, 2, 1L<<0, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, key_released, &mlx);
	mlx_loop_hook(mlx.mlx, loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
