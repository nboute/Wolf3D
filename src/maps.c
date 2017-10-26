/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 18:34:12 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:49:56 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_maze_loop(t_mlx *mlx)
{
	if (mlx->map->map[(int)mlx->cam.posx][(int)mlx->cam.posy] == 1)
		ft_load_screen(mlx);
	else
		ft_draw_arrow(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	ft_map_fct(t_mlx *mlx)
{
	if (mlx->map->id == 1)
		ft_maze_loop(mlx);
}

void	ft_create_default_map(t_map *map)
{
	int			i;
	int			j;
	static int	n = 0;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		if (!(map->map[i] = (char*)malloc(sizeof(char) * 32)))
			ft_exit(NULL);
		while (++j < 32)
		{
			if (i == 0 || i == 4 || j == 0 || j == 31)
			{
				n = ((n + 1) % (map->nbwalls - 2)) + map->nbfloors + 2;
				map->map[i][j] = n;
			}
			else if (i == 1 && j == 1)
				map->map[i][j] = map->nbfloors;
			else if (i == 2 && j == 1)
				map->map[i][j] = map->nbfloors + 1;
			else
				map->map[i][j] = j % map->nbfloors;
		}
	}
}

t_map	*ft_start_map(void)
{
	t_map	*map;
	int		i;

	i = 0;
	map = new_map();
	get_map_textures(0, map);
	if (!(map->map = (char**)malloc(sizeof(char*) * 5)))
		ft_exit(NULL);
	ft_create_default_map(map);
	map->width = 5;
	map->height = 32;
	map->startx = 2;
	map->starty = 16;
	map->id = 0;
	while (i < map->nbsprites)
	{
		add_sprite(map, i, 2.0, 7.5 + (double)i);
		i++;
	}
	return (map);
}

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
		map = slidegen(16, 3000);
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
		mlx->mapdata = ft_getmazedata(mlx, 0, 0);
	mlx->loading = 0;
	return (map);
}
