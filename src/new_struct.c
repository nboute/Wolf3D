/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 16:44:10 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:46:17 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdlib.h>

t_mlx		*init_mlx(t_mlx *ptr)
{
	if (!ptr)
		ft_exit(NULL);
	ptr->img = NULL;
	ptr->height = 0;
	ptr->width = 0;
	ptr->data = NULL;
	ptr->imgdata = NULL;
	ptr->map = NULL;
	ptr->mapwid = 0;
	ptr->keys[0].key = KEY_UP;
	ptr->keys[1].key = KEY_DOWN;
	ptr->keys[2].key = KEY_LEFT;
	ptr->keys[3].key = KEY_RIGHT;
	ptr->keys[0].pressed = 0;
	ptr->keys[1].pressed = 0;
	ptr->keys[2].pressed = 0;
	ptr->keys[3].pressed = 0;
	ptr->movespeed = 0;
	ptr->rotspeed = 0;
	ptr->loading = 0;
	ptr->mapdata = NULL;
	ptr->time = 0;
	ptr->oldtime = 0;
	ptr->frametime = 0;
	return (ptr);
}

t_map		*new_map(void)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		ft_exit(NULL);
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

t_sprite	*add_sprite(t_map *map, int texnum, double x, double y)
{
	t_sprite	*tmp;
	int			i;

	if (!map->nbsprites)
		return (NULL);
	tmp = map->sprites;
	if (!(map->sprites =
				(t_sprite*)malloc(sizeof(t_sprite) * (map->nbspr + 1))))
		ft_exit(NULL);
	i = 0;
	while (i < map->nbspr && tmp)
	{
		map->sprites[i] = tmp[i];
		i++;
	}
	map->nbspr++;
	map->sprites[i].x = x;
	map->sprites[i].y = y;
	map->sprites[i].texture = texnum;
	if (tmp)
		free(tmp);
	return (map->sprites);
}
