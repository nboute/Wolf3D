/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_basics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:29:10 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:47:06 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../inc/bitmap.h"
#include <locale.h>

int		exit_clean(void *mlx)
{
	free_map(((t_mlx*)mlx)->map);
	exit(0);
}

int		ft_exit(void *ret)
{
	if (ret)
		exit(0);
	ft_putendl("An error happened, you can sprawl on the floor, \
			take a fetal position and start crying now");
	exit(-1);
}

int		main(void)
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
	mlx_hook(mlx.win, 17, 1L << 17, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_released, &mlx);
	mlx_loop_hook(mlx.mlx, looper, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
