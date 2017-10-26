/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:40:56 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 19:04:23 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitmap.h"
#include <stdlib.h>
#include "../inc/header.h"
#include <stdio.h>

int		**load_sprite(int texid)
{
	if (texid == 0)
		return (bmp_to_array(TEXTURES"uwut.bmp", 64, 64));
	else if (texid == 1)
		return (bmp_to_array(TEXTURES"barrel.bmp", 64, 64));
	return (NULL);
}

void	load_textures_p2(char **textnames, t_map *map, int *spralphas, int i)
{
	char	*tmp;

	while (++i < map->nbwalls)
	{
		tmp = ft_strjoin(TEXTURES, textnames[i + 2]);
		map->walls[i] = bmp_to_array(tmp, 64, 64);
		ft_strdel(&tmp);
	}
	i = -1;
	while (++i < map->nbfloors)
	{
		tmp = ft_strjoin(TEXTURES, textnames[i + map->nbwalls + 3]);
		map->floors[i] = bmp_to_array(tmp, 64, 64);
		ft_strdel(&tmp);
	}
	i = -1;
	while (++i < map->nbsprites)
	{
		tmp = ft_strjoin(TEXTURES, textnames
				[i + map->nbwalls + map->nbfloors + 4]);
		map->sprtex[i].text = bmp_to_array(tmp, 64, 64);
		spralphas[i] = map->sprtex[i].text[0][0];
		map->sprtex[i].alpha = spralphas[i];
		ft_strdel(&tmp);
	}
}

void	load_textures(char **textnames, t_map *map, int *spralphas)
{
	int	i;

	if (map->nbwalls)
		if (!(map->walls = (int***)malloc(sizeof(int**) * map->nbwalls)))
			ft_exit(NULL);
	if (map->nbfloors)
		if (!(map->floors = (int***)malloc(sizeof(int**) * map->nbfloors)))
			ft_exit(NULL);
	if (map->nbsprites)
		if (!(map->sprtex = (t_sprtex*)malloc(sizeof(t_sprtex)
						* map->nbsprites)))
			ft_exit(NULL);
	load_textures_p2(textnames, map, spralphas, -1);
	i = 0;
	while (textnames[i])
		ft_strdel(&textnames[i++]);
}
