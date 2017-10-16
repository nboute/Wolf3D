/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 18:34:12 by nboute            #+#    #+#             */
/*   Updated: 2017/10/12 20:13:58 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdio.h>

t_map	*ft_start_map(void)
{
	t_map	*map;
	size_t	i;
	size_t	j;
	static size_t	n = 0;

	i = 0;
	map = new_map();
	get_map_textures(0, map);
	map->width = 5;
	map->height = 32;
	if (!(map->map = (char**)malloc(sizeof(char*) * 5)))
		ft_exit(NULL);
	while (i < 5)
	{
		j = 0;
		if (!(map->map[i] = (char*)malloc(sizeof(char) * 32)))
		ft_exit(NULL);
		while (j < 32)
		{
			if (i == 0 || i == 4 || j == 0 || j == 31)
			{
				n = ((n + 1) % (map->nbwalls - 2)) + map->nbfloors + 2;
				map->map[i][j] = n;
			}
			else if (i == 1 && j == 1)
				map->map[i][j] = map->nbfloors;
			else if (i == 2  && j == 1)
				map->map[i][j] = map->nbfloors + 1;
			else
			{
				map->map[i][j] = j % map->nbfloors;
			}
			j++;
		}
		i++;
	}
	getchar();
	map->startx = 2;
	map->starty = 16;
	map->id = 0;
//	if (map->sprites)
//		free(map->sprites);
	if (!(map->sprites = (t_sprite*)malloc(sizeof(t_sprite) * 2)))
		ft_exit(NULL);
	map->sprites[0].x = 2.0;
	map->sprites[0].y = 9.5;
	map->sprites[0].texture = 4;
	map->sprites[1].x = 2.0;
	map->sprites[1].y = 10.5;
	map->sprites[1].texture = 5;
	map->nbspr = 2;
	return (map);
}
