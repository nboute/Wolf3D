/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:40:56 by nboute            #+#    #+#             */
/*   Updated: 2017/10/12 20:20:49 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitmap.h"
#include <stdlib.h>
#include "../inc/header.h"

int		**load_wall(int wallId)
{
	if (wallId == 0)
		return (bmp_to_array(TEXT_PATH"brickwall_dark.bmp", 64, 64));
	else if (wallId == 1)
		return (bmp_to_array(TEXT_PATH"slide_block.bmp", 64, 64));
	else if (wallId == 2)
		return (bmp_to_array(TEXT_PATH"warp_maze.bmp", 64, 64));
	else if(wallId == 3)
		return (bmp_to_array(TEXT_PATH"warp_slide.bmp", 64, 64));
	else if (wallId == 4)
		return (bmp_to_array(TEXT_PATH"slide_block_2.bmp", 64, 64));
	else if (wallId == 5)
		return (bmp_to_array(TEXT_PATH"slide_block_3.bmp", 64, 64));
	else if (wallId == 6)
		return (bmp_to_array(TEXT_PATH"slide_block_4.bmp", 64, 64));
	return (NULL);
}

int		**load_floor(int	flrId)
{
	if (flrId == 0)
		return (bmp_to_array(TEXT_PATH"gravel.bmp", 64, 64));
	else if (flrId == 1)
		return (bmp_to_array(TEXT_PATH"slide_floor.bmp", 64, 64));
	else if (flrId == 2)
		return (bmp_to_array(TEXT_PATH"brickfloor.bmp", 64, 64));
	else if (flrId == 3)
		return (bmp_to_array(TEXT_PATH"red_dall.bmp", 64, 64));
	return (NULL);
}

int		**load_sprite(int	texId)
{
	if (texId == 0)
		return (bmp_to_array(TEXT_PATH"uwut.bmp", 64, 64));
	else if (texId == 1)
		return (bmp_to_array(TEXT_PATH"barrel.bmp", 64, 64));
	return (NULL);
}

/*

int		***load_text(t_map *map, int mapId)
{
	int	***textures;
	int	i;
	int	j;

	if (mapId == 0)
		i = 10;
	else if (mapId == 1)
		i = 3;
	else
		i = 6;
	map->nbtextures = i;
	map->nbsprites = (map->id != 0)? 1 : 2;
	if (map->id == 2)
		map->nbsprites = 0;
	if (!(textures = (int***)malloc(sizeof(int**) * i)))
		ft_exit(NULL);
	i = 0;
	if (mapId == 1)
	{
		textures[0] = load_floor(mapId - 1);
		textures[1] = load_sprite(mapId - 1);
		textures[2] = load_wall(mapId - 1);
	}
	else if (mapId == 2)
	{
		textures[0] = load_floor(mapId - 1);
		textures[1] = load_sprite(mapId - 1);
		textures[2] = load_wall(mapId - 1);
		textures[3] = load_wall(mapId + 2);
		textures[4] = load_wall(mapId + 3);
		textures[5] = load_wall(mapId + 4);
	}
	else
	{
		j = -1;
		while (++j < 4)
			textures[j] = load_floor(j);
		j--;
		while (++j < 6)
			textures[j] = load_sprite(j - 4);
		j--;
		while (++j < 10)
			textures[j] = load_wall(j - 6);
	}
	return (textures);*/

#include <stdio.h>

void	load_textures(char **textnames, t_map *map, int *spralphas)
{
	int		i;
	char	*tmp;

	ft_putendl("loading textures...");
	tmp = NULL;
	if (!(map->walls = (int***)malloc(sizeof(int**) * map->nbwalls)))
		ft_exit(0);
	if (!(map->floors = (int***)malloc(sizeof(int**) * map->nbfloors)))
		ft_exit(0);
	if (map->nbsprites)
		if (!(map->sprtex = (t_sprtex*)malloc(sizeof(t_sprtex)
						* map->nbsprites)))
			ft_exit(0);
	i = 0;
	while (i < map->nbwalls)
	{
		tmp = ft_strjoin(TEXT_PATH, textnames[i + 2]);
		map->walls[i] = bmp_to_array(tmp , 64, 64);
		ft_strdel(&tmp);
		i++;
	}
	i = 0;
	while (i < map->nbfloors)
	{
		tmp = ft_strjoin(TEXT_PATH, textnames[i + map->nbwalls + 3]);
		map->floors[i] = bmp_to_array(tmp , 64, 64);
		i++;
	}
	i = 0;
	while (i < map->nbsprites)
	{
		tmp = ft_strjoin(TEXT_PATH, textnames
				[i + map->nbwalls + map->nbfloors + 4]);
		map->sprtex[i].text = bmp_to_array(tmp, 64, 64);
		spralphas[i] = map->sprtex[i].text[0][0];
		map->sprtex[i].alpha = spralphas[i];
		ft_strdel(&tmp);
		i++;
	}
	getchar();
	ft_putendl("no shiet at all o_o");
	ft_putendl("textures loaded");
}
