/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:25:14 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 15:46:55 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>

void	rotate_view(double rotspeed, t_mlx *mlx)
{
	double	tmp;

	tmp = mlx->cam.dirX;
	mlx->cam.dirX = mlx->cam.dirX * cos(rotspeed)
		- mlx->cam.dirY * sin(rotspeed);
	mlx->cam.dirY = tmp * sin(rotspeed) + mlx->cam.dirY * cos(rotspeed);
	tmp = mlx->cam.planeX;
	mlx->cam.planeX = mlx->cam.planeX * cos(rotspeed)
		- mlx->cam.planeY * sin(rotspeed);
	mlx->cam.planeY = tmp * sin(rotspeed) + mlx->cam.planeY * cos(rotspeed);
}

void	ft_move_slide(t_mlx *mlx)
{
	double	dirX;
	double	dirY;

	dirX = 0;
	dirY = mlx->movespeed * mlx->frametime;
	if (mlx->movespeed < 50)
		mlx->movespeed =
			ft_dmap(mlx->cam.posY, ((mlx->map->height * 2) / 3), 8, 50);
	if (mlx->keys[0].pressed && !mlx->keys[1].pressed)
		dirY += mlx->movespeed / 2 * mlx->frametime;
	else if (mlx->keys[1].pressed && !mlx->keys[0].pressed)
		dirY += -mlx->movespeed / 2 * mlx->frametime;
	if (mlx->keys[2].pressed && !mlx->keys[3].pressed)
		dirX = -2 * mlx->frametime;
	else if (mlx->keys[3].pressed && !mlx->keys[2].pressed)
		dirX = 2 * mlx->frametime;
	if ((int)(mlx->cam.posY + dirY + 0.1) >= mlx->map->height - 10)
			load_map(0, &mlx->map, mlx);
		if (mlx->map->map[(int)(mlx->cam.posX + dirX)][(int)((mlx->cam.posY
					+ dirY + 0.1))]
				>= mlx->map->hit)
			ft_load_screen(mlx);
		else
		{
			mlx->cam.posY += dirY;
			mlx->cam.posX += dirX;
		}
}

void	ft_move_2(t_mlx *mlx, double val[4], double hbx[2])
{
	char	**map;

	map = mlx->map->map;
	val[2] = mlx->cam.posX - val[0];
	val[3] = mlx->cam.posY - val[1];
	if (mlx->keys[1].pressed && !mlx->keys[0].pressed && mlx->map->id != 2)
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
	if (mlx->keys[2].pressed && !mlx->keys[3].pressed)
		rotate_view(mlx->rotspeed, mlx);
	else if (mlx->keys[3].pressed && !mlx->keys[2].pressed)
		rotate_view(-mlx->rotspeed, mlx);
}

void	ft_move(t_mlx *mlx)
{
	double	hbx[2];
	double	val[4];
	char	**map;

	map = mlx->map->map;
	hbx[0] = (mlx->cam.dirX > 0) ? 0.10 : -0.10;
	hbx[1] = (mlx->cam.dirY > 0) ? 0.10 : -0.10;
	val[0] = mlx->cam.dirX * (5.0 * mlx->frametime);
	val[1] = mlx->cam.dirY * (5.0 * mlx->frametime);
	val[2] = mlx->cam.posX + val[0];
	val[3] = mlx->cam.posY + val[1];
	if (mlx->map->id == 2)
		ft_move_slide(mlx);
	if (mlx->keys[0].pressed && !mlx->keys[1].pressed && mlx->map->id != 2)
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
		ft_move_2(mlx, val, hbx);
}
