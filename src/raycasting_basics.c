/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_basics->c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:52:16 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 18:28:26 by nboute           ###   ########.fr       */
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
	free_map(mlx->map);
   }*/

// PARTIE A REFAIRE
void	ft_exit(void *idc)
{
	idc = NULL;
	ft_putendl("An error happened, you can go on the floor, \
			take a fetal position and start crying now");
	exit(-1);
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

void	ft_maze_loop(t_mlx *mlx)
{
	if (mlx->map->map[(int)mlx->cam.posX][(int)mlx->cam.posY] == 1)
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
	ft_putendl("start RC");
		ft_threads(mlx);
	ft_putendl("end RC");
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
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
	ft_putendl("end loop");
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
			if (text[i][j])
				free(text[i][j]);
			j++;
		}
		if (text[i])
			free(text[i]);
		i++;
	}
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
	if (map->sprtex)
	{
		while (i < map->nbsprites)
			free_text(&map->sprtex[i++].text, 1, TEXWID);
		free(map->sprtex);
	}
	if (map->walls)
	{
		free_text(map->walls, map->nbwalls, TEXWID);
		free(map->walls);
	}
	if (map->floors)
	{
		free_text(map->floors, map->nbfloors, TEXWID);
		free(map->floors);
	}
	if (map)
		free(map);
	return (1);
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
//	map->textures = load_text(map, map->id);
	map->hit = map->nbfloors;
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
