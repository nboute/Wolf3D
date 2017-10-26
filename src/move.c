/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:25:14 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:46:03 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <math.h>

int		ft_try_hit_front(t_mlx *mlx, double diry, double dirx, double posy)
{
	double	iter;

	iter = -1;
	while (++iter + 2 < diry)
	{
		if (posy + iter <= 1 || posy + 1 >= mlx->map->height - 1 ||
				mlx->cam.posx + dirx <= 1.1 || mlx->cam.posx + dirx >=
				((double)mlx->map->width - 1.1))
			return (-1);
		if (mlx->map->map[(int)mlx->cam.posx][(int)(posy + iter)]
				>= mlx->map->hit)
			return (-1);
		if (mlx->map->map[(int)(mlx->cam.posx + dirx * iter / diry + 0.10)]
				[(int)((mlx->cam.posy + iter))] >= mlx->map->hit &&
				mlx->map->map[(int)(mlx->cam.posx + dirx * iter / diry - 0.10)]
				[(int)(mlx->cam.posy + iter)] >= mlx->map->hit)
			return (-1);
	}
	if (mlx->map->map[(int)(mlx->cam.posx + dirx)][(int)(posy + diry)]
			>= mlx->map->hit)
		return (-1);
	mlx->cam.posx += dirx;
	mlx->cam.posy += diry;
	return (0);
}

void	ft_move_slide(t_mlx *mlx)
{
	double	dirx;
	double	diry;

	dirx = 0;
	mlx->movespeed =
		ft_dmap(mlx->cam.posy, ((mlx->map->height * 2) / 3), 8, 50);
	diry = mlx->movespeed * mlx->frametime;
	if (mlx->keys[0].pressed && !mlx->keys[1].pressed)
		diry += mlx->movespeed / 2 * mlx->frametime;
	else if (mlx->keys[1].pressed && !mlx->keys[0].pressed)
		diry += -mlx->movespeed / 2 * mlx->frametime;
	if (mlx->keys[2].pressed && !mlx->keys[3].pressed)
		dirx = -2 * mlx->frametime;
	else if (mlx->keys[3].pressed && !mlx->keys[2].pressed)
		dirx = 2 * mlx->frametime;
	if ((int)(mlx->cam.posy + diry + 0.1) >= mlx->map->height - 10)
		load_map(0, &mlx->map, mlx);
	else
	{
		if (ft_try_hit_front(mlx, diry, dirx, mlx->cam.posy))
			ft_load_screen(mlx);
	}
}

int		try_move(t_mlx *mlx, double *hbx, double *val, char **map)
{
	val[2] = mlx->cam.posx + val[0];
	val[3] = mlx->cam.posy + val[1];
	hbx = NULL;
	if (val[2] < 1 || val[2] >= mlx->map->width - 1 || val[3] < 1
			|| val[3] > mlx->map->height - 1)
		return (0);
	if (map[(int)(val[2] + 0.10)][(int)(mlx->cam.posy + 0.10)] < mlx->map->hit
			&& map[(int)(val[2] - 0.10)][(int)(mlx->cam.posy + 0.10)]
			< mlx->map->hit && map[(int)(val[2] - 0.10)]
			[(int)(mlx->cam.posy - 0.10)] < mlx->map->hit &&
			map[(int)(val[2] + 0.10)][(int)(mlx->cam.posy - 0.10)]
			< mlx->map->hit)
		mlx->cam.posx += val[0];
	if (map[(int)(mlx->cam.posx + 0.10)][(int)(val[3] + 0.10)] < mlx->map->hit
			&& map[(int)(mlx->cam.posx - 0.10)][(int)(val[3] + 0.10)]
			< mlx->map->hit && map[(int)(mlx->cam.posx + 0.10)][(int)(val[3]
				- 0.10)] < mlx->map->hit && map[(int)(mlx->cam.posx - 0.10)]
			[(int)(val[3] - 0.10)] < mlx->map->hit)
		mlx->cam.posy += val[1];
	return (0);
}

void	ft_move_2(t_mlx *mlx, double val[4], double hbx[2])
{
	char	**map;

	if (mlx->map->id == 2)
		return ;
	map = mlx->map->map;
	if (mlx->keys[1].pressed && !mlx->keys[0].pressed && mlx->map->id != 2)
	{
		hbx[0] *= -1;
		hbx[1] *= -1;
		val[0] *= -1;
		val[1] *= -1;
		try_move(mlx, hbx, val, map);
	}
	if (mlx->keys[2].pressed && !mlx->keys[3].pressed)
		rotate_view(mlx->rotspeed, mlx);
	else if (mlx->keys[3].pressed && !mlx->keys[2].pressed)
		rotate_view(-mlx->rotspeed, mlx);
}

void	ft_move(t_mlx *mlx, char **map)
{
	double	hbx[2];
	double	val[4];

	hbx[0] = (mlx->cam.dirx > 0) ? 0.10 : -0.10;
	hbx[1] = (mlx->cam.diry > 0) ? 0.10 : -0.10;
	val[0] = mlx->cam.dirx * (5.0 * mlx->frametime);
	val[1] = mlx->cam.diry * (5.0 * mlx->frametime);
	if (mlx->map->id == 2)
		ft_move_slide(mlx);
	if (mlx->keys[0].pressed && !mlx->keys[1].pressed && mlx->map->id != 2)
		try_move(mlx, hbx, val, map);
	ft_move_2(mlx, val, hbx);
}
