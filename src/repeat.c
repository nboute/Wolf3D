/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:45:00 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 20:59:36 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>
#include "../inc/raycast.h"

void			ft_place_pixel(int color, int x, int y, t_mlx *mlx)
{
	*(unsigned*)(mlx->data + x * mlx->bpx / 8 + y * mlx->size) = color;
}

void			*raycast(void *data)
{
	t_mlx		*mlx;
	t_vects		*v;
	int			i;
	t_sprinf	s;

	mlx = ((t_thread*)data)->data;
	i = ((t_thread*)data)->id;
	v = &mlx->vectors[i];
	v->x = (i * mlx->width) / RAYCAST_THREADS - 1;
	i = ((i + 1) * mlx->width) / RAYCAST_THREADS;
	while (++v->x < i)
	{
		raycast_setparams(mlx, v, v->x);
		raycast_dda_alg(mlx, v);
		raycast_calc_wall(mlx, v);
		mlx->zbuff[v->x] = v->pwalldt;
		raycast_calc_floor(mlx, v);
	}
	if (mlx->map->nbspr && mlx->map->nbsprites && mlx->map->sprites)
		raycast_sprites(mlx, mlx->vectors, &s);
	if (mlx->map->nbspr && s.sprord)
		free(s.sprord);
	if (mlx->map->nbspr && s.sprord)
		free(s.sprdist);
	return (NULL);
}

void			ft_threads(t_mlx *mlx)
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

int				looper(void *ptr)
{
	t_mlx		*mlx;

	mlx = (t_mlx*)ptr;
	mlx->frametime = (double)(mlx->time - mlx->oldtime)
		/ (double)CLOCKS_PER_SEC;
	mlx->oldtime = mlx->time;
	mlx->time = clock();
	if (!mlx->loading)
	{
		mlx->cam.target = 0;
		ft_threads(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		ft_move(mlx, mlx->map->map);
		ft_map_fct(mlx);
	}
	else
		sleep(2);
	return (0);
}
