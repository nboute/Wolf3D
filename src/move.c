/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:25:14 by nboute            #+#    #+#             */
/*   Updated: 2017/09/26 15:20:16 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_move_slide(t_mlx *mlx, t_keys *k)
{
	double	dirX;
	double	dirY;

	dirX = 0;
	dirY = mlx->movespeed * mlx->frametime;
	if (mlx->movespeed < 50)
		mlx->movespeed = ft_dmap(mlx->cam.posY, ((mlx->map->height * 2) / 3), 8, 50);
	if (k[0].pressed && !k[1].pressed)
		dirY += mlx->movespeed / 2 * mlx->frametime;
	else if (k[1].pressed && !k[0].pressed)
		dirY += -mlx->movespeed / 2 * mlx->frametime;
	if (k[2].pressed && !k[3].pressed)
		dirX = -2 * mlx->frametime;
	else if (k[3].pressed && !k[2].pressed)
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
	val[0] = mlx->cam.dirX * (5.0 * mlx->frametime);
	val[1] = mlx->cam.dirY * (5.0 * mlx->frametime);
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
