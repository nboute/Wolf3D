/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:05:09 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 18:31:11 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

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
	int	i;

	i = -1;
	mlx = (t_mlx*)ptr;
	if (mlx->loading)
	{
		mlx->loading = 0;
		load_map(0, &mlx->map, mlx);
	}
	else if (key >= KEY_LEFT || key <= KEY_UP)
		while (++i < 4)
		{
			if (mlx->keys[i].key == key)
			{
				if (!mlx->keys[i].pressed)
					mlx->keys[i].pressed = 1;
				return (0);
			}
		}
	else if (key == 14)
		if (mlx->map->id == 1)
		{
			mlx->cam.posX = ((t_mazedata*)(mlx->mapdata))->exit[0] + 0.5;
			mlx->cam.posY = ((t_mazedata*)(mlx->mapdata))->exit[1] + 0.5;
		}
	return (0);
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
			if (mlx->cam.target == mlx->map->nbfloors)
				mlx->map = load_map(1, &mlx->map, mlx);
			else if (mlx->cam.target == mlx->map->nbfloors + 1)
				mlx->map = load_map(2, &mlx->map, mlx);
		}
	}
	return (0);
}
