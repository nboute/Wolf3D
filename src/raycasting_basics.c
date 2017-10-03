/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_basics->c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:52:16 by nboute            #+#    #+#             */
/*   Updated: 2017/10/02 17:09:43 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../inc/bitmap.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void			ft_place_pixel(int color, int x, int y, t_mlx *mlx)
{
	*(unsigned*)(mlx->data + x * mlx->bpx / 8 + y * mlx->size) = color;
///	*(unsigned*)(mlx->imgdata + x * mlx->bpx / 8 + y * mlx->size) = color;
}
/*
   int		exit_clean(void* mlx)
   {

   }*/

// PARTIE A REFAIRE
void	ft_exit(void *idc)
{
	idc = NULL;
	ft_putendl("Couldn't malloc");
	exit(-1);
}

int		***load_text(t_map *map, int mapId)
{
	int	***textures;
	int	i;
	int	j;

	if (mapId == 0)
		i = 10;
	else if (mapId == 1)
		i = 3;
	else
		i = 6;
	map->nbtextures = i;
	map->nbsprites = (map->id != 0)? 1 : 2;
	if (map->id == 2)
		map->nbsprites = 0;
	if (!(textures = (int***)malloc(sizeof(int**) * i)))
		ft_exit(NULL);
	i = 0;
	if (mapId == 1)
	{
		textures[0] = load_floor(mapId - 1);
		textures[1] = load_sprite(mapId - 1);
		textures[2] = load_wall(mapId - 1);
	}
	else if (mapId == 2)
	{
		textures[0] = load_floor(mapId - 1);
		textures[1] = load_sprite(mapId - 1);
		textures[2] = load_wall(mapId - 1);
		textures[3] = load_wall(mapId + 2);
		textures[4] = load_wall(mapId + 3);
		textures[5] = load_wall(mapId + 4);
	}
	else
	{
		j = -1;
		while (++j < 4)
			textures[j] = load_floor(j);
		j--;
		while (++j < 6)
			textures[j] = load_sprite(j - 4);
		j--;
		while (++j < 10)
			textures[j] = load_wall(j - 6);
	}
	return (textures);
}
/*
int		***gen_text(void)
{
	int	x;
	int	y;
	int	***textures;
	int	i;

	if (!(textures = (int***)malloc(sizeof(int**) * 14)))
		ft_exit(NULL);
	x = 0;
	i = 4;
	textures[0] = bmp_to_array(TEXT_PATH"brickwall_dark.bmp", 64, 64);
	textures[1] = bmp_to_array(TEXT_PATH"red_dall.bmp", 64, 64);
	textures[2] = bmp_to_array(TEXT_PATH"warp_maze.bmp", 64, 64);
	textures[3] = bmp_to_array(TEXT_PATH"warp_slide.bmp", 64, 64);
	textures[8] = bmp_to_array(TEXT_PATH"barrel.bmp", 64, 64);
	textures[9] = bmp_to_array(TEXT_PATH"wolf_pillar.bmp", 64, 64);
	textures[10] = bmp_to_array(TEXT_PATH"greenlight.bmp", 64, 64);
	textures[11] = bmp_to_array(TEXT_PATH"uwut.bmp", 64, 64);
	while (i < 14)
	{
		if (!(textures[i] = (int**)malloc(sizeof(int*) * 64)))
			ft_exit(NULL);
		x = 0;
		while (x < 64 && (i <= 7 || i >= 12))
		{
			y = 0;
			if (!(textures[i][] = (int*)malloc(sizeof(int) * 64)))
				ft_exit(NULL);
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
}*/

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
	if (mlx->loading)
	{
		mlx->loading = 0;
		load_map(0, &mlx->map, mlx);
		return (0);
	}
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
		printf("%lf|%lf\n", mlx->cam.posX, mlx->cam.posY);
	}
	else if (key == 14)
	{
		if (mlx->map->id == 1)
		{
			mlx->cam.posX = ((t_mazedata*)(mlx->mapdata))->exit[0] + 0.5;
			mlx->cam.posY = ((t_mazedata*)(mlx->mapdata))->exit[1] + 0.5;
		}
	}
	return (0);
}
// FIN PARTIE A CLEAN
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
// PARTIE A CLEAN
void	ft_move_slide(t_mlx *mlx, t_keys *k)
{
	double	dirX;
	double	dirY;

	dirX = 0;
	dirY = mlx->movespeed * mlx->frametime;
	if (mlx->movespeed < 50)
		mlx->movespeed = ft_dmap(mlx->cam.posY, ((mlx->map->height * 2) / 3), 8, 50);
/*	if (mlx->cam.posY < mlx->map->height / 10 && mlx->movespeed < 12)
		mlx->movespeed += mlx->cam.posY / (mlx->map->height * 8);
	else if (mlx->cam.posY < (mlx->map->height * 3) / 10 && mlx->cam.posY >= mlx->map->height / 4 && mlx->movespeed < 25)
		mlx->movespeed += mlx->cam.posY / (mlx->map->height * 16);
	else if (mlx->cam.posY < (mlx->map->height * 3) / 5 && mlx->cam.posY >= mlx->map->height / 2 && mlx->movespeed < 37)
		mlx->movespeed += mlx->cam.posY / (mlx->map->height * 32);
	else if (mlx->movespeed < 50)
		mlx->movespeed += mlx->cam.posY / (mlx->map->height * 32);*/
	if (k[0].pressed && !k[1].pressed)
		dirY += mlx->movespeed / 2 * mlx->frametime;
	else if (k[1].pressed && !k[0].pressed)
		dirY += -mlx->movespeed / 2 * mlx->frametime;
	if (k[2].pressed && !k[3].pressed)
		dirX = -2 * mlx->frametime;
	else if (k[3].pressed && !k[2].pressed)
		dirX = 2 * mlx->frametime;
	if ((int)(mlx->cam.posY + dirY + 0.1) >= mlx->map->height - 10)
		{
			load_map(0, &mlx->map, mlx);
			ft_putendl("youwin");
		}
		if (mlx->map->map[(int)(mlx->cam.posX + dirX)][(int)((mlx->cam.posY
					+ dirY + 0.1))]
				>= mlx->map->hit)
		{
			mlx->loading = 1;
			ft_load_screen(mlx);
			ft_putendl("youlost");
		}
		else
		{
			mlx->cam.posY += dirY;
			mlx->cam.posX += dirX;
		}
}
//
void	ft_move_2(t_mlx *mlx, t_keys *k, double val[4], double hbx[2])
{
	char	**map;

	map = mlx->map->map;
	val[2] = mlx->cam.posX - val[0];
	val[3] = mlx->cam.posY - val[1];
	if (k[1].pressed && !k[0].pressed && mlx->map->id != 2)
	{
		if (val[2] - hbx[0] >= 0 && (int)(val[2] - hbx[0]) < mlx->map->width)
			if (map[(int)(val[2] - hbx[0])][(int)(mlx->cam.posY - hbx[1])] <
					mlx->map->hit && map[(int)val[2]][(int)mlx->cam.posY]
					< mlx->map->hit)
				mlx->cam.posX -= val[0];
		if (val[3] - hbx[1] >= 0 && (int)(val[3] - hbx[1]) < mlx->map->height)
			if (map[(int)(mlx->cam.posX - hbx[0])][(int)(val[3] - hbx[1])] <
					mlx->map->hit && map[(int)mlx->cam.posX][(int)val[3]] <
					mlx->map->hit)
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
	val[0] = fmin(mlx->cam.dirX * (5.0 * mlx->frametime), 0.25);
	val[1] = fmin(mlx->cam.dirY * (5.0 * mlx->frametime), 0.25);
	val[2] = mlx->cam.posX + val[0];
	val[3] = mlx->cam.posY + val[1];
	if (mlx->map->id == 2)
		ft_move_slide(mlx, k);
	if (k[0].pressed && !k[1].pressed && mlx->map->id != 2)
	{
		if (val[2] + hbx[0] >= 0 && (int)(val[2] + hbx[0]) < mlx->map->width)
			if (map[(int)(val[2] + hbx[0])][(int)(mlx->cam.posY + hbx[1])] <
				mlx->map->hit && map[(int)(val[2])][(int)(mlx->cam.posY)] <
				mlx->map->hit)
			{
				mlx->cam.posX += val[0];
			}
		if (val[3] + hbx[1] >= 0 && (int)(val[3] + hbx[1]) < mlx->map->height)
			if (map[(int)(mlx->cam.posX + hbx[0])][(int)(val[3] + hbx[1])] <
					mlx->map->hit && map[(int)(mlx->cam.posX)][(int)(val[3])]
					< mlx->map->hit)
				mlx->cam.posY += val[1];
	}
	if (mlx->map->id != 2)
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
		if (mlx->map->map[v->mapX][v->mapY] >= mlx->map->hit)
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
	texX = 63 - (int)(v->wallX * (double)64);
	i = v->drawstart;
	while (i < v->drawend)
	{
		d = i * 256 - mlx->height * 128 + v->lineH * 128;
		texY = ((d * 64) / v->lineH) / 256;
		if (v->side == 1)
			ft_place_pixel(mlx->map->textures[texNum][texY][texX], v->x, i, mlx);
//			ft_place_pixel(mlx->map->wall[texNum][texY][texX], v->x, i, mlx);
		else
			ft_place_pixel((mlx->map->textures[texNum][texY][texX] >> 1)
					& 8355711, v->x, i, mlx);
		i++;
	}
}

void		raycast_calc_wall(t_mlx *mlx, t_vects *v)
{
	int	texNum;
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
	if (mlx->map->id == 0)
		texNum = mlx->map->map[v->mapX][v->mapY];
	else if (mlx->map->id == 2)
		texNum = mlx->map->map[v->mapX][v->mapY] + 1;
	else
		texNum = 2;
	raycast_draw_wall(mlx, v, texNum);
}

void		raycast_draw_floor(t_mlx *mlx, t_vects *v,
		double	floorXWall, double floorYWall)
{
	int	i;
	t_flrinf	t;
	int	texNum;

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
		texNum = mlx->map->id == 0 ? ((int)t.currFlrX + (int)t.currFlrY) % 4 : 0;
		if (mlx->map->map[(int)t.currFlrX][(int)t.currFlrY] == -1)
			texNum = 1;
		ft_place_pixel(((mlx->map->textures[texNum][t.flrTexY][t.flrTexX] >> 1)
						& 8355711), v->x, i, mlx);
//		ft_place_pixel(((mlx->map->floor[texNum][t.flrTexY][t.flrTexX] >> 1)
//						& 8355711), v->x, i, mlx);
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
		texX = (int)(256 * (x - (-s->sprWidth / 2 + s->sprscreenX)) * 64
				/ s->sprWidth) / 256;
		if (texX > 0 && s->transfY > 0 && x < mlx->width && s->transfY < mlx->zbuff[x])
		{
			y = v->drawstartY - 1;
			while (++y < v->drawendY)
			{
				texY = (((y * 256 - mlx->height * 128 + s->sprHeight * 128)
							* 64) / s->sprHeight) / 256;
				if (texY < 0)
					texY = 0;
				col = mlx->map->textures[mlx->map->sprites
					[s->sprOrd[s->sprid]].texture][texY][texX];
				if ((col & 0x00FFFFFF) != 0 && (col & 0x00FFFFFF) != 0x00191919)
					ft_place_pixel(col, x, y, mlx);
			}
		}
	}
}

void		raycast_calc_sprites(t_mlx * mlx, t_vects *v, t_sprinf *s)
{
	s->sprX = mlx->map->sprites[s->sprOrd[s->sprid]].x - mlx->cam.posX;
	s->sprY = mlx->map->sprites[s->sprOrd[s->sprid]].y - mlx->cam.posY;
	if (s->sprX == 0)
		s->sprX = 0.01;
	if (s->sprY == 0)
		s->sprY = 0.01;
	s->invDet = 1.0 / (mlx->cam.planeX * mlx->cam.dirY
			- mlx->cam.dirX * mlx->cam.planeY);
	s->transfX = s->invDet * (mlx->cam.dirY * s->sprX
			- mlx->cam.dirX * s->sprY);
	s->transfY = s->invDet * (-mlx->cam.planeY * s->sprX
			+ mlx->cam.planeX * s->sprY);
	s->sprscreenX = (int)((mlx->width / 2) * (1 + s->transfX / s->transfY));
	s->sprHeight = abs((int)(mlx->height / s->transfY));
	v->drawstartY = -s->sprHeight / 2 + mlx->height / 2;
	if (v->drawstartY < 0)
		v->drawstartY = 0;
	v->drawendY = s->sprHeight / 2 + mlx->height / 2;
	if (v->drawendY >= mlx->height)
		v->drawendY = mlx->height - 1;
	if (v->drawendY < 0)
		v->drawendY = 0;
	s->sprWidth = abs((int)(mlx->width / s->transfY));
	v->drawstartX = -s->sprWidth / 2 + s->sprscreenX;
	if (v->drawstartX < 0)
		v->drawstartX = 0;
	v->drawendX = s->sprWidth / 2 + s->sprscreenX;
	if (v->drawendX >= mlx->width)
		v->drawendX = mlx->width - 1;
	if (v->drawendX < 0)
		v->drawendX = 0;
}

int		raycast_sprites(t_mlx *mlx, t_vects *v)
{
	int			i;
	t_sprinf	s;

	i = 0;
	if (!(s.sprOrd = (int*)malloc(sizeof(int) * mlx->map->nbtextures)))
		ft_exit(NULL);
	if (!(s.sprDist = (double*)malloc(sizeof(double) * mlx->map->nbtextures)))
		ft_exit(NULL);
	while (i < mlx->map->nbsprites)
	{
		s.sprOrd[i] = i;
		s.sprDist[i] = ((mlx->cam.posX - mlx->map->sprites[i].x) *
			(mlx->cam.posX - mlx->map->sprites[i].x) + (mlx->cam.posY -
			mlx->map->sprites[i].y) * (mlx->cam.posY - mlx->map->sprites[i].y));
		i++;
	}
	if (mlx->map->nbsprites > 1)
		ft_combsort(s.sprOrd, s.sprDist, mlx->map->nbsprites);
	s.sprid = 0;
	while (s.sprid < mlx->map->nbsprites)
	{
			raycast_calc_sprites(mlx, v, &s);
		if ((s.sprX >= 0.5 || s.sprX <= -0.5) || (s.sprY >= 0.5 || s.sprY <= -0.5))
			raycast_draw_sprites(mlx, v, &s, 0);
		s.sprid++;
	}
	return (1);
}

void		*raycast(void	*data)
{
	t_mlx	*mlx;
	t_vects	*v;
	int		i;

	mlx = ((t_thread*)data)->data;
		i = ((t_thread*)data)->id;
		v = &mlx->vectors[i];
		v->x = (i * mlx->width) / RAYCAST_THREADS;
		i = ((i + 1) * mlx->width) / RAYCAST_THREADS;
		while (v->x < i)
		{
			raycast_setparams(mlx, v, v->x);
			raycast_dda_alg(mlx, v);
			raycast_calc_wall(mlx, v);
			mlx->zbuff[v->x] = v->pwalldt;
			raycast_calc_floor(mlx, v);
			v->x++;
			if (mlx->map->nbsprites)
				raycast_sprites(mlx, v);
		}
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
//	ft_bzero(mlx->data, mlx->bpx / 8 * mlx->height * mlx->width);
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
//	ft_fast_memcpy(mlx->data, mlx->data, mlx->bpx / 8 * mlx->height * mlx->width);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_move_mobs(t_mlx *mlx)
{
	int	dirX;
	int	dirY;

	dirX = 0;
	dirY = 0;
	if (mlx->cam.posX < mlx->map->sprites[0].x + 0.5)
		dirX = -1;
	else if (mlx->cam.posX > mlx->map->sprites[0].x - 0.5)
		dirX = 1;
	if (mlx->cam.posY < mlx->map->sprites[0].y + 0.5)
		dirY = -1;
	else if (mlx->cam.posY > mlx->map->sprites[0].y - 0.5)
		dirY = 1;
	mlx->map->sprites[0].x += (double)dirX * 0.01;
	mlx->map->sprites[0].y += (double)dirY * 0.01;

	mlx->map->sprites[0].x = roundf(100 * mlx->map->sprites[0].x) / 100;
	mlx->map->sprites[0].y = roundf(100 * mlx->map->sprites[0].y) / 100;
}

void	ft_invert_cols_square_2d_matrix(int **dest, int **src, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dest[i][j] = src[size - i - 1][j];
			j++;
		}
		i++;
	}
}

void	ft_invert_rows_square_2d_matrix(int **dest, int **src, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dest[i][j] = src[i][size -j -1];
			j++;
		}
		i++;
	}
}

void	ft_transpose_square_2d_matrix(int **dest, int **src, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dest[j][i] = src[i][j];
			j++;
		}
		i++;
	}
}

int		ft_rot_p2(int **dest, int **src, int size, int angle)
{
	if (angle == 90)
		ft_invert_rows_square_2d_matrix(dest, src, size);
	else if (angle == 180 || angle == 270)
		ft_invert_cols_square_2d_matrix(dest, src, size);
	return (0);
}

int		**ft_rotate_2d(int **src, int size, int angle)
{
	int	i;
	int	**dest;
	int	**tmp;

	i = -1;
	if (!(dest = (int**)malloc(sizeof(int*) * size)))
		ft_exit(NULL);
	if (!(tmp = (int**)malloc(sizeof(int*) * size)))
		ft_exit(NULL);
	while (++i < size)
	{
		if (!(tmp[i] = (int*)malloc(sizeof(int) * size)) || 
				!(dest[i] = (int*)malloc(sizeof(int) * size)))
			ft_exit(NULL);
	}
	if (angle == 90)
		ft_transpose_square_2d_matrix(tmp, src, size);
	else if (angle == 180)
		ft_invert_rows_square_2d_matrix(tmp, src, size);
	else if (angle == 270)
		ft_transpose_square_2d_matrix(tmp, src, size);
	ft_rot_p2(dest, tmp, size, angle);
	return (dest);
}

short	ft_getarrowdir(double x, double y, double Ex, double Ey)
{
	int		angle;

	angle = ((int)((atan2(Ex * y - Ey * x, Ex * x + Ey * y)) * 180) / PI);
	if (angle < 0)
		angle += 360;
	return (((angle + 22) / 45) % 8);
}

void	ft_draw_arrow(t_mlx *mlx)
{
	int	***arrow;
	if (mlx->map->id != 1)
		return ;
//	double	dirX;
//	double	dirY;
//	short	dir;
	arrow = ((t_mazedata*)mlx->mapdata)->arrow;
//	dirX = ((t_mazedata*)mlx->mapdata)->exit[0] - mlx->cam.posX;
//	dirY = ((t_mazedata*)mlx->mapdata)->exit[1] - mlx->cam.posX;
	mlx->arrowdir = ft_getarrowdir(mlx->cam.dirX, mlx->cam.dirY, ((t_mazedata*)(mlx->mapdata))->exit[0] - mlx->cam.posX, ((t_mazedata*)mlx->mapdata)->exit[1] - mlx->cam.posY);
	int	i = 0;
	while (i < 64)
	{
		int	j = 0;
		while (j < 64)
		{
			if ((arrow[mlx->arrowdir][i][j] & 0x00FFFFFF) != 0x00FEFEFF)
				ft_place_pixel(arrow[mlx->arrowdir][i][j], i + 566, j + 32, mlx);
			j++;
		}
		i++;
	}
}


void	ft_maze_loop(t_mlx *mlx)
{
	if (mlx->map->map[(int)mlx->cam.posX][(int)mlx->cam.posY] == -1)
	{
		ft_load_screen(mlx);
	}
	else
	{
		ft_putendl("shitty code part");
		ft_draw_arrow(mlx);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_map_fct(t_mlx *mlx)
{
	if (mlx->map->id == 1)
	{
		ft_maze_loop(mlx);
	}
}

int	loop(void *ptr)
{
	t_mlx *mlx;

	mlx = (t_mlx*)ptr;
	printf("%lf        |       %lf\n", mlx->movespeed, mlx->cam.posY);
	mlx->frametime = (double)(mlx->time - mlx->oldtime) / (double)CLOCKS_PER_SEC;
	mlx->oldtime = mlx->time;
	mlx->time = clock();
	if (!mlx->loading)
	{
		mlx->cam.target = 0;
		mlx->cam.posX = roundf(mlx->cam.posX * 100) / 100;
		mlx->cam.posY = roundf(mlx->cam.posY * 100) / 100;
		if (mlx->map->id == 1)
			ft_move_mobs(mlx);
		ft_threads(mlx);
		ft_move(mlx);
		ft_map_fct(mlx);
	}
	else
	{
		sleep(2);
//		ft_fast_memcpy(mlx->imgdata, mlx->data, mlx->bpx / 8 * mlx->height * mlx->width);
//		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	//	raycast(mlx);
	return (0);
}
#include <locale.h>
#include <stdio.h>

int		free_text(int ***text, int nb, int wid)
{
	int	i;
	int	j;

	if (!text)
		return (0);
	i = 0;
	while (i < nb && text[i])
	{
		j = 0;
		while (j < wid && text[i][j])
		{
			free(text[i][j]);
			j++;
		}
		free(text[i]);
		i++;
	}
	free(text);
	return (0);
}

int		free_map(t_map *map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	if (map->map)
	{
		while (i < map->width && map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	
	i = 0;
	if (map->sprites)
		free(map->sprites);
	free_text(map->textures, map->nbtextures, TEXWID);
	return (0);
}

void	load_load(t_mlx *mlx)
{
	mlx = 0;
}

t_map	*load_map(int id, t_map **oldmap, t_mlx *mlx)
{
	t_map	*map;
//	load_load(mlx, id);
	ft_putendl("loading map n textures\n");
	if (oldmap)
		free_map(*oldmap);
	mlx->loading = 1;
	if (id == 0)
		map = ft_start_map();
	else if (id == 1)
	{
		map = mazegen(64, 4);
/*		mlx->exit = bmp_to_array(TEXT_PATH"arrow.bmp", 64, 64);
		int	i = 0;
		mlx->exittmp = (t_point**)malloc(sizeof(t_point*) * 64);
		while (i < 64)
			mlx->exittmp[i++] = (t_point*)malloc(sizeof(t_point) * 64);
*/	}
	else
		map = slidegen(16, 2000, 20);
	mlx->cam.posX = map->startx + 0.5;
	mlx->cam.posY = map->starty + 0.5;
	mlx->cam.dirX = -1;
	mlx->cam.dirY = 0;
	mlx->cam.planeX = 0;
	mlx->cam.planeY = 0.66;
	mlx->movespeed = (map->id == 2) ? 8 : 0.5;
	rotate_view(-PI / 2, mlx);
	map->textures = load_text(map, map->id);
	map->hit = (map->id == 0)? 6 : 1;
	mlx->map = map;
	if (id == 1)
		mlx->mapdata = ft_getmazedata(mlx);
/*	int	i;
	i = 0;
	if (oldmap)
	{
	while (i < (*oldmap)->width)
	free((*oldmap)->map[i++]);
	free((*oldmap)->map);
	free(*oldmap);
	}
	*/
	mlx->loading = 0;
	ft_putstr("map and textures both loaded\n");
	return (map);
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
			if (mlx->cam.target == 8)
				mlx->map = load_map(1, &mlx->map, mlx);
			else if (mlx->cam.target == 9)
				mlx->map = load_map(2, &mlx->map, mlx);
		}
	}
	return (0);
}

int	main(void)
{
	t_mlx mlx;

	t_map maze;

	mlx.loading = 1;
	setlocale(LC_ALL, "");
	srand(time(NULL));
	maze.height = 64;
	maze.width = 64;
//	mazegen(&maze, maze.height, 4);
//	mlx.map = &maze;
	mlx.map = load_map(0, NULL, &mlx);
	/*	mlx.map->maphei = 64;
		mlx.map->mapwid = 64;
		if (!(mlx.map->map = (char**)malloc(sizeof(char*) * (mlx.map->maphei + 1))))
		return (-1);
		*/
	mlx.cam.posX = mlx.map->startx + 0.5;
	mlx.cam.posY = mlx.map->starty + 0.5;
	if (!(mlx.keys = (t_keys*)malloc(sizeof(t_keys) * 4)))
		ft_exit(NULL);
	mlx.keys[0].key = KEY_UP;
	mlx.keys[1].key = KEY_DOWN;
	mlx.keys[2].key = KEY_LEFT;
	mlx.keys[3].key = KEY_RIGHT;
	mlx.keys[0].pressed = 0;
	mlx.keys[1].pressed = 0;
	mlx.keys[2].pressed = 0;
	mlx.keys[3].pressed = 0;
	mlx.height = 1000;
	mlx.width = 1200;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.width, mlx.height, "Wolf3D");
	mlx.img = NULL;
	/*	int	y;
		int	x = 0;
		while (x < mlx.map->mapwid)
		{
		y = 0;
		//mlx.map->map[x] = (char*)malloc(sizeof(char) * (mlx.map->maphei + 1));
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
	mlx.rotspeed = 0.05;
	mlx.time = 0;
	mlx.oldtime = 0;
	//	mlx.map->map[x] = NULL;
	mlx_hook(mlx.win, 2, 1L<<0, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, key_released, &mlx);
	mlx_mouse_hook(mlx.win, mouse_pressed, &mlx);
	mlx.loading = 0;
	mlx_loop_hook(mlx.mlx, loop, &mlx);
	//	mlx_hook(win, 17, 1L<<17, exit(clean), (void*)mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
