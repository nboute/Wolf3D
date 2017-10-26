/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_elems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:28:34 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 20:37:49 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	destroy_arrows(t_mazedata *maze)
{
	int			i;
	int			j;

	i = 0;
	if (maze)
	{
		while (i < 8 && maze->arrow)
		{
			j = 0;
			while (j < TEXWID && maze->arrow[i])
			{
				if (maze->arrow[i][j])
					free(maze->arrow[i][j]);
				j++;
			}
			if (maze->arrow[i])
				free(maze->arrow[i]);
			i++;
		}
		if (maze->arrow)
			free(maze->arrow);
	}
}

int		free_text(int ***text, int nb, int wid)
{
	int	i;
	int	j;

	if (!text)
		return (0);
	i = 0;
	while (i < nb)
	{
		j = 0;
		while (j < wid && text[i][j])
		{
			if (text[i][j])
				free(text[i][j]);
			j++;
		}
		if (text[i])
			free(text[i]);
		i++;
	}
	return (0);
}

void	free_map_p2(t_map *map)
{
	int	i;

	i = 0;
	if (map->sprtex)
	{
		while (i < map->nbsprites)
			free_text(&(map->sprtex[i++].text), 1, TEXWID);
		free(map->sprtex);
	}
	if (map->walls)
	{
		free_text(map->walls, map->nbwalls, TEXWID);
		free(map->walls);
	}
	if (map->floors)
	{
		free_text(map->floors, map->nbfloors, TEXWID);
		free(map->floors);
	}
	if (map)
		free(map);
}

int		free_map(t_map *map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	if (map->map)
	{
		while (i < map->width && map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	if (map->sprites)
		free(map->sprites);
	if (map)
		free_map_p2(map);
	return (1);
}
