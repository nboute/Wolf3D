/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_basics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:29:10 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 16:51:15 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../inc/bitmap.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <locale.h>


int		exit_clean(void* mlx)
{
	free_map(((t_mlx*)mlx)->map);
	exit(0);
}

int		ft_exit(void	*ret)
{
	if (ret)
		exit(0);
	ft_putendl("An error happened, you can sprawl on the floor, \
			take a fetal position and start crying now");
	exit(-1);
}
/*
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
		i = -1;
		while (++i < amount - gap)
			if (dist[i] < dist[i + gap])
			{
				ft_swap(dist + i, dist + i + gap, sizeof(double));
				ft_swap(order + i, order + i + gap, sizeof(int));
				swap = 0;
			}
	}
}
*/
/*
t_map	*load_map(int id, t_map **oldmap, t_mlx *mlx)
{
	t_map	*map;

	if (oldmap)
		free_map(*oldmap);
	mlx->loading = 1;
	if (id == 0)
		map = ft_start_map();
	else if (id == 1)
		map = mazegen(64, 4);
	else
		map = slidegen(16, 2000);
	mlx->cam.posx = map->startx + 0.5;
	mlx->cam.posy = map->starty + 0.5;
	mlx->cam.dirx = -1;
	mlx->cam.diry = 0;
	mlx->cam.planex = 0;
	mlx->cam.planey = 0.66;
	mlx->movespeed = (map->id == 2) ? 8 : 0.5;
	rotate_view(-PI / 2, mlx);
	map->hit = map->nbfloors;
	mlx->map = map;
	if (id == 1)
		mlx->mapdata = ft_getmazedata(mlx);
	mlx->loading = 0;
	return (map);
}
*/
int	main(void)
{
	t_mlx mlx;

	init_mlx(&mlx);
	mlx.loading = 1;
	setlocale(LC_ALL, "");
	srand(time(NULL));
	rotate_view(PI, &mlx);
	mlx.height = 1000;
	mlx.width = 1200;
	mlx.map = load_map(0, NULL, &mlx);
	mlx.rotspeed = 0.05;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.width, mlx.height, "Wolf3D");
	mlx_hook(mlx.win, 17, 1L<<17, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 1L<<0, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, key_released, &mlx);
	mlx_mouse_hook(mlx.win, mouse_pressed, &mlx);
	mlx_loop_hook(mlx.mlx, looper, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
