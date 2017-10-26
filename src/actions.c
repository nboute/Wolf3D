/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:05:09 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 21:08:47 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			key_released(int key, void *ptr)
{
	t_mlx	*mlx;
	int		i;

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

int			key_pressed_p2(int key, t_mlx *mlx)
{
	if (key == 14)
	{
		if (mlx->map->id == 1)
		{
			mlx->cam.posx = ((t_mazedata*)(mlx->mapdata))->exit[0] + 0.5;
			mlx->cam.posy = ((t_mazedata*)(mlx->mapdata))->exit[1] + 0.5;
		}
	}
	else if (key == 53)
		ft_exit(mlx);
	else if (key == 49 && mlx->map->id == 0)
	{
		if (mlx->cam.target == mlx->map->nbfloors)
			mlx->map = load_map(1, &mlx->map, mlx);
		else if (mlx->cam.target == mlx->map->nbfloors + 1)
			mlx->map = load_map(2, &mlx->map, mlx);
	}
	return (0);
}

int			key_pressed(int key, void *ptr)
{
	t_mlx	*mlx;
	int		i;

	i = -1;
	mlx = (t_mlx*)ptr;
	if (mlx->loading)
	{
		mlx->loading = 0;
		load_map(0, &mlx->map, mlx);
	}
	else if (key >= KEY_LEFT && key <= KEY_UP)
		while (++i < 4)
		{
			if (mlx->keys[i].key == key)
				mlx->keys[i].pressed = 1;
			if (mlx->keys[i].key == key)
				return (0);
		}
	else
		return (key_pressed_p2(key, mlx));
	return (0);
}
