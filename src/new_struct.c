/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 16:44:10 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 17:57:30 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_mlx	*new_mlx(void)
{
	t_mlx	*ptr;

	if (!(ptr = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_exit(0);
	ptr->mlx = NULL;
	ptr->win = NULL;
	ptr->img = NULL;
	ptr->height = 0;
	ptr->width = 0;
	ptr->data = NULL;
	ptr->imgdata = NULL;
	ptr->bpx = 0;
	ptr->size = 0;
	ptr->end = 0;
	ptr->map = NULL;
	ptr->mapwid = 0;
	ptr->maphei = 0;
	ptr->keys = NULL;
	ptr->movespeed = 0;
	ptr->rotspeed = 0;
	ptr->loading = 0;
	ptr->mapdata = NULL;
	ptr->time = 0;
	ptr->oldtime = 0;
	ptr->frametime = 0;
	return (ptr);
}

t_map	*new_map(void)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		ft_exit(0);
	map->id = 0;
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->startx = 0;
	map->starty = 0;
	map->textures = NULL;
	map->sprites = NULL;
	map->walls = NULL;
	map->floors = NULL;
	map->sprtex = NULL;
	map->nbsprites = 0;
	map->nbspr = 0;
	map->nbtextures = 0;
	map->nbwalls = 0;
	map->nbfloors = 0;
	map->out = 0;
	map->hit = 0;
	return (map);
}

t_sprite	*add_sprite(t_map *map, int	texNum, double x, double y)
{
	t_sprite	*tmp;
	int			i;

	tmp = map->sprites;
	if (!tmp)
	if (!(map->sprites =
				(t_sprite*)malloc(sizeof(t_sprite) * (map->nbsprites + 1))))
		ft_exit(NULL);
	i = 0;
	while (i < map->nbsprites && tmp)
	{
		map->sprites[i] = tmp[i];
		i++;
	}
	map->nbsprites++;
	map->sprites[i].x = x;
	map->sprites[i].y = y;
	map->sprites[i].texture = texNum;
	return (map->sprites);
}
