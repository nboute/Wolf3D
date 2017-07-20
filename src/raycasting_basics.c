/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_basics->c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:52:16 by nboute            #+#    #+#             */
/*   Updated: 2017/07/20 20:28:43 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


t_sprite g_sprite[numSprites] =
{
	{28.0, 28.0, 11},
	{31.5, 32.5, 10}, //green light in front of playerstart
	//	green lights in every room
	{18.5, 4.5, 10},
	{10.5, 4.5, 10},
	{10.5, 12.5, 10},
	{4.5, 6.5, 10},
	{4.5, 20.5, 10},
	{4.5, 14.5, 10},
	{14.5, 20.5, 10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 12.5, 9},
	{18.5, 14.5, 9},

	//some barrels around the map
	{21.5, 2.5, 8},
	{16.5, 32.5, 8},
	{16.0, 32.8, 8},
	{16.2, 32.2, 8},
	{10.5, 16.5, 8},
	{10.0, 16.1, 8},
	{10.5, 14.8, 8},
};

void			ft_place_pixel(int color, int x, int y, t_mlx *mlx)
{
	*(unsigned*)(mlx->data + x * mlx->bpx / 8 + y * mlx->size) = color;
}
/*
   int		exit_clean(void* mlx)
   {

   }*/

int		noise(void)
{
	int	noise;

	noise = (rand() % 32768) / 32768;
	return (65536 * noise + 256 * noise + noise);
}

int		text_formulas(int t, int x, int y)
{
	int	xorcolor;
	int	ycolor;
	int	xycolor;

	xorcolor = (x * 256 / 64) ^ (y * 256 / 64);
	ycolor = y * 256 / 64;
	xycolor = y * 128 / 64 + x * 128 / 64;
	if (t == 0)
		return (65536 * 254 * (x != y && x != 64 - y));
	else if (t == 1)
		return (xycolor + 256 * xycolor + 65536 * xycolor);
	else if (t == 2)
		return (256 * xycolor + 65536 * xycolor);
	else if (t == 3)
		return (xorcolor + 256 * xorcolor + 65536 * xorcolor);
	else if (t == 4)
		return (256 * xorcolor);
	else if (t == 5)
		return (65536 * 192 * (x % 16 && y % 16));
	else if (t == 6)
		return (65536 * ycolor);
	else if (t == 7)
		return (128 + 256 * 128 + 65536 * 128);
	else if (t == 8)
		return (noise());
	return (65536 * (t - 8) * 32 + 256 * x * 4 + y * 4);
}

int		***gen_text(void)
{
	int	x;
	int	y;
	int	***textures;
	int	i;

	textures = (int***)malloc(sizeof(int**) * 14);
	x = 0;
	i = 3;
	textures[0] = bmp_to_array("./brickwall_dark.bmp", 64, 64);
	textures[1] = bmp_to_array("./red_dall.bmp", 64, 64);
	textures[2] = bmp_to_array("./warp_maze.bmp", 64, 64);
	textures[8] = bmp_to_array("./barrel.bmp", 64, 64);
	textures[9] = bmp_to_array("./wolf_pillar.bmp", 64, 64);
	textures[10] = bmp_to_array("./greenlight.bmp", 64, 64);
	textures[11] = bmp_to_array("./uwut.bmp", 64, 64);
	while (i < 14)
	{
		textures[i] = (int**)malloc(sizeof(int*) * 64);
		x = 0;
		while (x < 64 && (i <= 7 || i >= 12))
		{
			y = 0;
			textures[i][x] = (int*)malloc(sizeof(int) * 64);
			while (y < 64)
			{
				textures[i][x][y] = text_formulas(i, x, y);
				y++;
			}
			x++;
		}
		if (i == 7)
			i = 12;
		else
			i++;
	}
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
		print_grid(mlx->map, (int)mlx->cam.posX, (int)mlx->cam.posY);
	}
	else if (key == 14)
	{
		int	x, y;
		x = 0;
		while (x < mlx->map->width)
		{
			y = 0;
			while (y < mlx->map->height)
			{
				if (mlx->map->map[x][y] == -1 && (mlx->map->map[x][y + 1] == 0
							|| mlx->map->map[x][y - 1] == 0 ||
							mlx->map->map[x + 1][y] == 0 ||
							mlx->map->map[x - 1][y] == 0))
				{
					mlx->cam.posX = x + 0.5;
					mlx->cam.posY = y + 0.5;
					return (1);
				}
				y++;
			}
			x++;
		}
	}
	return (0);
}

void	rotate_view(double rotspeed, t_mlx *mlx)
{
	double	tmp;

	tmp = mlx->cam.dirX;
	mlx->cam.dirX = mlx->cam.dirX * cos(rotspeed) - mlx->cam.dirY * sin(rotspeed);
	mlx->cam.dirY = tmp * sin(rotspeed) + mlx->cam.dirY * cos(rotspeed);
	tmp = mlx->cam.planeX;
	mlx->cam.planeX = mlx->cam.planeX * cos(rotspeed) - mlx->cam.planeY * sin(rotspeed);
	mlx->cam.planeY = tmp * sin(rotspeed) + mlx->cam.planeY * cos(rotspeed);
}

void	ft_move_2(t_mlx *mlx, t_keys *k, double val[4], double hbx[2])
{
	char	**map;

	map = mlx->map->map;
	val[2] = mlx->cam.posX - val[0];
	val[3] = mlx->cam.posY - val[1];
	if (k[1].pressed && !k[0].pressed)
	{
		if (val[2] - hbx[0] >= 0 && (int)(val[2] - hbx[0]) < mlx->map->width)
			if (map[(int)(val[2] - hbx[0])][(int)(mlx->cam.posY - hbx[1])] <= 0
				&& map[(int)val[2]][(int)mlx->cam.posY] <= 0)
				mlx->cam.posX -= val[0];
		if (val[3] - hbx[1] >= 0 && (int)(val[3] - hbx[1]) < mlx->map->height)
			if (map[(int)(mlx->cam.posX - hbx[0])][(int)(val[3] - hbx[1])] <= 0
					&& map[(int)mlx->cam.posX][(int)val[3]] <= 0)
				mlx->cam.posY -= val[1];
	}
	if (k[2].pressed && !k[3].pressed)
		rotate_view(mlx->rotspeed, mlx);
	else if (k[3].pressed && !k[2].pressed)
		rotate_view(-mlx->rotspeed, mlx);
}

void	ft_move(t_mlx *mlx)
{
	t_keys	*k;
	double	hbx[2];
	double	val[4];
	char	**map;

	map = mlx->map->map;
	hbx[0] = (mlx->cam.dirX > 0) ? 0.10 : -0.10;
	hbx[1] = (mlx->cam.dirY > 0) ? 0.10 : -0.10;
	k = mlx->keys;
	val[0] = mlx->cam.dirX * mlx->movespeed;
	val[1] = mlx->cam.dirY * mlx->movespeed;
	val[2] = mlx->cam.posX + val[0];
	val[3] = mlx->cam.posY + val[1];
	if (k[0].pressed && !k[1].pressed)
	{
		if (val[2] + hbx[0] >= 0 && (int)(val[2] + hbx[0] < mlx->map->width))
			if (map[(int)(val[2] + hbx[0])][(int)(mlx->cam.posY + hbx[1])] <= 0
					&& map[(int)(val[2])][(int)(mlx->cam.posY)] <= 0)
				mlx->cam.posX += val[0];
		if (val[3] + hbx[1] >= 0 && (int)(val[3] + hbx[1]) < mlx->map->width)
			if (map[(int)(mlx->cam.posX + hbx[0])][(int)(val[3] + hbx[1])] <= 0
					&& map[(int)(mlx->cam.posX)][(int)(val[3])] <= 0)
				mlx->cam.posY += val[1];
	}
	ft_move_2(mlx, k, val, hbx);
}

void	ft_combsort(int *order, double *dist, int amount)
{
	int		gap;
	short	swap;
	int		i;

	gap = amount;
	swap = 1;
	while (gap > 1 || swap)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swap = 0;
		i = 0;
		while (i < amount - gap)
		{
			if (dist[i] < dist[i + gap])
			{
				ft_swap(dist + i, dist + i + gap, sizeof(double));
				ft_swap(order + i, order + i + gap, sizeof(int));
				swap = 0;
			}
			i++;
		}
	}
}

void		raycast_setparams(t_mlx *mlx, t_vects *v, int	x)
{
	v->camX = ft_dmap(x, mlx->width, -1, 1);
	v->rayposX = mlx->cam.posX;
	v->rayposY = mlx->cam.posY;
	v->raydirX = mlx->cam.dirX + mlx->cam.planeX * v->camX;
	v->raydirY = mlx->cam.dirY + mlx->cam.planeY * v->camX;
	v->mapX = (int)v->rayposX;
	v->mapY = (int)v->rayposY;
	v->deltadistX = sqrt(1 + (v->raydirY * v->raydirY) /
			(v->raydirX * v->raydirX));
	v->deltadistY = sqrt(1 + (v->raydirX * v->raydirX) /
			(v->raydirY * v->raydirY));
	v->stepX = (v->raydirX < 0) ? -1 : 1;
	v->stepY = (v->raydirY < 0) ? -1 : 1;
	if (v->raydirX < 0)
		v->sidedistX = (v->rayposX - v->mapX) * v->deltadistX;
	else
		v->sidedistX = (v->mapX + 1.0 - v->rayposX) * v->deltadistX;
	if (v->raydirY < 0)
		v->sidedistY = (v->rayposY - v->mapY) * v->deltadistY;
	else
		v->sidedistY = (v->mapY + 1.0 - v->rayposY) * v->deltadistY;
}

void		raycast_dda_alg(t_mlx *mlx, t_vects *v)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (v->sidedistX < v->sidedistY)
		{
			v->sidedistX += v->deltadistX;
			v->mapX += v->stepX;
			v->side = 0;
		}
		else
		{
			v->sidedistY += v->deltadistY;
			v->mapY += v->stepY;
			v->side = 1;
		}
		if (mlx->map->map[v->mapX][v->mapY] > 0)
			hit = 1;
	}
	if (v->x == mlx->height / 2)
		mlx->cam.target = mlx->map->map[v->mapX][v->mapY];
	if (v->side == 0)
		v->pwalldt = (v->mapX - v->rayposX + (1 - v->stepX) / 2) / v->raydirX;
	else
		v->pwalldt = (v->mapY - v->rayposY + (1 - v->stepY) / 2) / v->raydirY;
}

void		raycast_draw_wall(t_mlx *mlx, t_vects *v, int texNum)
{
	int	i;
	int	d;
	int	texY;
	int	texX;

	i = v->drawstart;
	texX = (int)(v->wallX * (double)64);
	texX = 64 - texX - 1;
	i = v->drawstart;
	if (mlx->map->map[v->mapX][v->mapY] == 2)
		texNum = 2;
	while (i < v->drawend)
	{
		d = i * 256 - mlx->height * 128 + v->lineH * 128;
		texY = ((d * 64) / v->lineH) / 256;
		if (v->side == 1)
			ft_place_pixel(mlx->map->textures[texNum][texX][texY], v->x, i, mlx);
		else
			ft_place_pixel((mlx->map->textures[texNum][texX][texY] >> 1)
					& 8355711, v->x, i, mlx);
		i++;
	}
}

void		raycast_calc_wall(t_mlx *mlx, t_vects *v)
{
	v->lineH = (int)(mlx->height / v->pwalldt);
	v->drawstart = -v->lineH / 2 + mlx->height / 2;
	if (v->drawstart < 0)
		v->drawstart = 0;
	v->drawend = v->lineH / 2 + mlx->height / 2;
	if (v->drawend >= mlx->height)
		v->drawend = mlx->height - 1;
	if (v->drawend >= mlx->height)
		v->drawend = mlx->height - 1;
	if (v->side == 0)
		v->wallX = v->rayposY + v->pwalldt * v->raydirY;
	else
		v->wallX = v->rayposX + v->pwalldt * v->raydirX;
	v->wallX -= floor(v->wallX);
	raycast_draw_wall(mlx, v, 0);
}

void		raycast_draw_floor(t_mlx *mlx, t_vects *v,
		double	floorXWall, double floorYWall)
{
	int	i;
	t_flrinf	t;

	t.distWall = v->pwalldt;
	t.distPlayer = 0.0;
	if (v->drawend < 0)
		v->drawend = mlx->height;
	i = v->drawend + 1;
	while (i < mlx->height)
	{
		t.currDist = mlx->height / (2.0 * i - mlx->height);
		t.weight = (t.currDist - t.distPlayer) / (t.distWall - t.distPlayer);
		t.currFlrX = t.weight * floorXWall + (1.0 - t.weight) * mlx->cam.posX;
		t.currFlrY = t.weight * floorYWall + (1.0 - t.weight) * mlx->cam.posY;
		t.flrTexX = (int)(t.currFlrX * 64) % 64;
		t.flrTexY = (int)(t.currFlrY * 64) % 64;
		if (mlx->map->map[(int)t.currFlrX][(int)t.currFlrY] == 0)
			ft_place_pixel(((mlx->map->textures[1][t.flrTexX][t.flrTexY] >> 1)
						& 8355711), v->x, i, mlx);
		else
			ft_place_pixel(((mlx->map->textures[6][t.flrTexX][t.flrTexY] >> 1)
						& 8355711), v->x, i, mlx);
		i++;
	}
}

void		raycast_calc_floor(t_mlx *mlx, t_vects *v)
{
	double	floorXWall;
	double	floorYWall;
	if (v->side == 0 && v->raydirX != 0)
	{
		floorXWall = v->mapX + ((v->raydirX > 0) ? 0 : 1.0);
		floorYWall = v->mapY + v->wallX;
	}
	else if (v->side == 1 && v->raydirY > 0)
	{
		floorXWall = v->mapX + v->wallX;
		floorYWall = v->mapY;
	}
	else
	{
		floorXWall = v->mapX + v->wallX;
		floorYWall = v->mapY + 1.0;
	}
	raycast_draw_floor(mlx, v, floorXWall, floorYWall);
}

void		raycast_draw_sprites(t_mlx *mlx, t_vects *v, t_sprinf *s, int col)
{
	int	x;
	int	texX;
	int	texY;
	int	y;

	x = v->drawstartX - 1;
	while (++x < v->drawendX)
	{
		texX = (int)(256 * (x - (-s->spriteWidth / 2 + s->spritescreenX)) * 64
				/ s->spriteWidth) / 256;
		if (s->transfY > 0 && x < mlx->width && s->transfY < mlx->zbuff[x])
		{
			y = v->drawstartY - 1;
			while (++y < v->drawendY)
			{
				texY = (((y * 256 - mlx->height * 128 + s->spriteHeight * 128)
							* 64) / s->spriteHeight) / 256;
				if (texY < 0)
					texY = 0;
				col = mlx->map->textures[g_sprite[s->spriteorder[s->sprid]].texture][texX][texY];
				if ((col & 0x00FFFFFF) != 0 && (col & 0x00FFFFFF) != 0x00191919)
					ft_place_pixel(col, x, y, mlx);
			}
		}
	}
}

void		raycast_calc_sprites(t_mlx * mlx, t_vects *v, t_sprinf *s)
{
	s->spriteX = g_sprite[s->spriteorder[s->sprid]].x - mlx->cam.posX;
	s->spriteY = g_sprite[s->spriteorder[s->sprid]].y - mlx->cam.posY;
	s->invDet = 1.0 / (mlx->cam.planeX * mlx->cam.dirY
			- mlx->cam.dirX * mlx->cam.planeY);
	s->transfX = s->invDet * (mlx->cam.dirY * s->spriteX
			- mlx->cam.dirX * s->spriteY);
	s->transfY = s->invDet * (-mlx->cam.planeY * s->spriteX
			+ mlx->cam.planeX * s->spriteY);
	s->spritescreenX = (int)((mlx->width / 2) * (1 + s->transfX / s->transfY));
	s->spriteHeight = abs((int)(mlx->height / s->transfY));
	v->drawstartY = -s->spriteHeight / 2 + mlx->height / 2;
	if (v->drawstartY < 0)
		v->drawstartY = 0;
	v->drawendY = s->spriteHeight / 2 + mlx->height / 2;
	if (v->drawendY >= mlx->height)
		v->drawendY = mlx->height - 1;
	if (v->drawendY < 0)
		v->drawendY = 0;
	s->spriteWidth = abs((int)(mlx->width / s->transfY));
	v->drawstartX = -s->spriteWidth / 2 + s->spritescreenX;
	if (v->drawstartX < 0)
		v->drawstartX = 0;
	v->drawendX = s->spriteWidth / 2 + s->spritescreenX;
	if (v->drawendX >= mlx->width)
		v->drawendX = mlx->width - 1;
	if (v->drawendX < 0)
		v->drawendX = 0;
}

void		raycast_sprites(t_mlx *mlx, t_vects *v)
{
	int			i;
	t_sprinf	s;

	i = 0;
	while (i < numSprites)
	{
		s.spriteorder[i] = i;
		s.spriteDistance[i] = ((mlx->cam.posX - g_sprite[i].x) *
				(mlx->cam.posX - g_sprite[i].x) + (mlx->cam.posY -
					g_sprite[i].y) * (mlx->cam.posY - g_sprite[i].y));
		i++;
	}
	ft_combsort(s.spriteorder, s.spriteDistance, numSprites);
	s.sprid = 0;
	while (s.sprid < numSprites)
	{
		raycast_calc_sprites(mlx, v, &s);
		raycast_draw_sprites(mlx, v, &s, 0);
		s.sprid++;
	}
}

void		*raycast(void	*data)
{
	t_mlx	*mlx;
	t_vects	*v;
	int		i;

	ft_putstr("WHYA\n");
	mlx = (t_mlx*)data;
	mlx = ((t_thread*)data)->data;
	i = ((t_thread*)data)->id;
	v = &mlx->vectors[i];
	v->x = (i * mlx->width) / RAYCAST_THREADS;
	i = ((i + 1) * mlx->width) / RAYCAST_THREADS;
	while (v->x < i)
	{
		raycast_setparams(mlx, v, v->x);
	ft_putstr("WHYC\n");
		raycast_dda_alg(mlx, v);
		raycast_calc_wall(mlx, v);
		mlx->zbuff[v->x] = v->pwalldt;
		raycast_calc_floor(mlx, v);
		v->x++;
	}
	ft_putstr("WHYB\n");
	if (mlx->map->id)
		raycast_sprites(mlx, v);
	return (NULL);
}

void	ft_threads(t_mlx *mlx)
{
	t_thread	t[RAYCAST_THREADS];
	int			i;
	int			ret;

	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpx, &mlx->size, &mlx->end);
	i = 0;
	ret = 0;
	while (i < RAYCAST_THREADS && !ret)
	{
		t[i].id = i;
		t[i].data = mlx;
		ret = pthread_create(&t[i].thread, NULL, raycast, (void*)(&t[i]));
		i++;
	}
	if (ret)
		exit(-1);
	i = 0;
	while (i < RAYCAST_THREADS)
		pthread_join(t[i++].thread, NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_move_mobs(t_mlx *mlx)
{
	int	dirX;
	int	dirY;

	dirX = 0;
	dirY = 0;
	if (mlx->cam.posX < g_sprite[0].x + 0.5)
		dirX = -1;
	else if (mlx->cam.posX > g_sprite[0].x - 0.5)
		dirX = 1;
	if (mlx->cam.posY < g_sprite[0].y + 0.5)
		dirY = -1;
	else if (mlx->cam.posY > g_sprite[0].y - 0.5)
		dirY = 1;
	g_sprite[0].x += (double)dirX * 0.02;
	g_sprite[0].y += (double)dirY * 0.02;
}

int	loop(void *ptr)
{
	t_mlx *mlx;

	mlx = (t_mlx*)ptr;
	ft_move(mlx);
	mlx->cam.target = 0;
	mlx->cam.posX = roundf(mlx->cam.posX * 100) / 100;
	mlx->cam.posY = roundf(mlx->cam.posY * 100) / 100;
	ft_move_mobs(mlx);
	ft_threads(mlx);
	//	raycast(mlx);
	return (0);
}
#include <locale.h>
#include <stdio.h>


t_map	*load_map(int id, t_map **oldmap, t_mlx *mlx)
{
	t_map	*map;
	ft_putchar('a');
	if (id == 0)
		map = ft_start_map(32, 32);
	else
		map = mazegen(64, 4);
	ft_putchar('b');
	if (oldmap)
	{
		map->textures = (*oldmap)->textures;
		map->nbtextures = 14;
		map->sprites = (*oldmap)->sprites;
		map->nbsprites = 19;
	}
	else
	{
		map->textures = gen_text();
		map->nbtextures = 14;
	}
	ft_putchar('c');
	mlx->cam.posX = mlx->map->startx + 0.5;
	mlx->cam.posY = mlx->map->starty + 0.5;
	mlx->cam.dirX = -1;
	mlx->cam.dirY = 0;
	mlx->cam.planeX = 0;
	mlx->cam.planeY = 0.66;
/*	int	i;
	i = 0;
	if (oldmap)
	{
		while (i < (*oldmap)->width)
			free((*oldmap)->map[i++]);
		free((*oldmap)->map);
		free(*oldmap);
	}
*/	return (map);
}

int	mouse_pressed(int button, int x, int y, void *data)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)data;
	x = 0;
	y = 0;
	if (mlx->map)
	{
		if (mlx->map->id == 0 && button == 1)
		{
			ft_putstr("test");
			if (mlx->cam.target == 2)
				mlx->map = load_map(1, &mlx->map, mlx);
			ft_putstr("testb\n");
		}
	}
	return (0);
}

int	main(void)
{
	t_mlx mlx;

	t_map maze;

	setlocale(LC_ALL, "");
	srand(time(NULL));
	maze.height = 64;
	maze.width = 64;
//	mazegen(&maze, maze.height, 4);
//	mlx.map = &maze;
	mlx.map = load_map(0, NULL, &mlx);
	mlx.map->textures = gen_text();
	/*	mlx.map->maphei = 64;
		mlx.map->mapwid = 64;
		if (!(mlx.map->map = (char**)malloc(sizeof(char*) * (mlx.map->maphei + 1))))
		return (-1);
		*/

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
	mlx_mouse_hook(mlx.win, mouse_pressed, &mlx);
	mlx_loop_hook(mlx.mlx, loop, &mlx);
	//	mlx_hook(win, 17, 1L<<17, exit(clean), (void*)mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
