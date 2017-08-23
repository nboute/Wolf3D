/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 18:34:12 by nboute            #+#    #+#             */
/*   Updated: 2017/07/24 17:44:52 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

t_map	*ft_start_map(void)
{
	t_map	*map;
	size_t	i;
	size_t	j;

	i = 0;
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		ft_exit(NULL);
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
				map->map[i][j] = 6 + (j % 2);
			else if (i == 1 && j == 1)
				map->map[i][j] = 8;
			else if (i == 2  && j == 1)
				map->map[i][j] = 9;
			else
				map->map[i][j] = j % 4;
			j++;
		}
		i++;
	}
	map->width = 5;
	map->height = 32;
	map->startx = 2;
	map->starty = 16;
	map->id = 0;
//	if (map->sprites)
//		free(map->sprites);
	if (!(map->sprites = (t_sprite*)malloc(sizeof(t_sprite) * 2)))
		ft_exit(NULL);
	map->sprites[0].x = 2.0;
	map->sprites[0].y = 10.0;
	map->sprites[0].texture = 4;
	map->sprites[1].x = 2.0;
	map->sprites[1].y = 11.0;
	map->sprites[1].texture = 5;
	map->nbsprites = 2;
	return (map);
}
