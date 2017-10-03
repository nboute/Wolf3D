/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:44:51 by nboute            #+#    #+#             */
/*   Updated: 2017/10/03 19:10:23 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitmap.h"
#include "../inc/header.h"
#include "../libft/libft.h"

/*
** Part that reads and loads textures according to the .inf files
** corresponding to a certain map
** .inf files are formatted this way:
** first line: total number of textures used for this map
** second line: total number of wall textures (i walls)
** line 3 -> i + 3 :  wall textures names
** line i + 4 :  total number of floor textures (j floors)
** line i + 5 -> i + j + 5 :  floor textures names
** line i + j + 6: total number of sprites textures (k sprites)
** line i + j + 7 -> i + j + k + 7: sprite textures names
*/

void	read_inf(int fd, t_map *map)
{
	char	buff[2048];
	char	**textnames;
	char	*ptr;
	int		i;

	i = read(fd, buff, 2047);
	close(fd);
	buff[i] = '\0';
	ptr = ft_strchr(buff, '\n');
	map->nbtextures = ft_atoi(buff);
	if (!(textnames = (char**)malloc(sizeof(char*) * (map->nbtextures + 1))))
		ft_exit(0);
	if (map->nbtextures)
		map->textures = (int***)malloc(sizeof(int**) * map->nbtextures);
	i = 0;
	map->nbwalls = ft_atoi(ptr);
	while (i <= map->nbwalls)
	{
		ptr = ft_strchr(ptr, '\n');
		textnames[i++] = ft_strndup(ptr, ft_strclen(ptr, '\n'));
	}
	map->nbfloors = ft_atoi(ptr);
	i = 0;
	while (i <= map->nbfloors)
	{
		ptr = ft_strchr(ptr, '\n');
		textnames[i++ + map->nbwalls] = ft_strndup(ptr, ft_strclen(ptr, '\n'));
	}
}

void	read_sprites(t_map *map, char *buff, char **textnames)
{
	int	i;
	int		*spralphas;

	map->nbsprites = ft_atoi(buff);
	spralphas = (int*)malloc(sizeof(int) * map->nbsprites);
	i = 0;
	while (i < map->nbsprites)
	{
		buff = ft_strchr(buff, '\n');
		spralphas[i] = ft_atoi(buff);
		buff = ft_strchr(buff, '\n');
		textnames[i + map->nbwalls + map->nbfloors] =
			ft_strndup(buff, ft_strclen(buff, '\n'));
		i++;
	}
	textnames[map->nbtextures] = NULL;
}

/*
**vals[0] fd
**vals[1] retour read
**vals[2] desc fichier (nombre de formats de maps disponibles)
*/
void	get_map_textures(unsigned short mapId, t_map *map)
{
	char	*buff;
	char	*ptr;
	int		vals[3];

	if (!(buff = (char*)malloc(sizeof(char) * 2048)))
		ft_exit(0);
	vals[0] = open("../desc/maps.inf", O_RDONLY);
	vals[1] = read(vals[0], buff, 2047);
	buff[vals[1]] = '\0';
	vals[2] = ft_atoi(buff);
	close(vals[0]);
	if (mapId >= vals[2])
		ft_exit(0);
	vals[1] = 0;
	ptr = buff;
	while (vals[1] <= vals[2] && vals[1] <= mapId)
	{
		ptr = ft_strchr(ptr, '\n');
		vals[1]++;
	}
	ptr = ft_strndup(ptr, ft_strclen(ptr, '\n'));
	vals[0] = open(ptr, O_RDONLY);
	ft_strdel(&ptr);
	ft_strdel(&buff);
	read_inf(vals[0], map);
}
