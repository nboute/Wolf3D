/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 14:44:51 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:47:20 by nboute           ###   ########.fr       */
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

void		read_inf_p2(int lines, char **tab, t_map *map)
{
	int		i;

	if (map->nbtextures + 3 > lines || map->nbtextures <= 1 ||
			lines > map->nbtextures + 4)
		ft_exit(NULL);
	map->nbwalls = ft_atoi(tab[1]);
	map->nbfloors = ft_atoi(tab[2 + map->nbwalls]);
	if (map->nbwalls <= 0 || map->nbfloors <= 0 ||
			map->nbwalls >= map->nbtextures || map->nbfloors >= map->nbtextures)
		ft_exit(NULL);
	if (map->nbwalls + map->nbfloors + 3 < lines)
		map->nbsprites = ft_atoi(tab[3 + map->nbwalls + map->nbfloors]);
	load_textures(tab, map);
	i = 0;
	while (tab[i])
		ft_strdel(&tab[i++]);
	free(tab);
}

int			try_open(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		ft_exit(NULL);
	return (fd);
}

void		read_inf(char *str, t_map *map)
{
	int		fd;
	int		i;
	char	buff[4096];
	char	**tab;

	if (!str)
		ft_exit(NULL);
	str = ft_strjoinn(DESC, str, ft_strclen(str, '\n'));
	fd = try_open(str);
	ft_strdel(&str);
	if ((i = read(fd, buff, 4095)) <= 0)
		ft_exit(NULL);
	close(fd);
	buff[i] = '\0';
	if (!(tab = ft_strsplit(buff, '\n')))
		ft_exit(NULL);
	i = 0;
	while (tab[i])
		i++;
	map->nbtextures = 0;
	if (i)
		map->nbtextures = ft_atoi(*tab);
	read_inf_p2(i, tab, map);
}

/*
**vals[0] fd
**vals[1] retour read
**vals[2] desc fichier (nombre de formats de maps disponibles)
*/

void		get_map_textures(unsigned short mapid, t_map *map)
{
	char	*buff;
	char	*ptr;
	int		vals[3];

	if (!(buff = (char*)malloc(sizeof(char) * 2048)))
		ft_exit(NULL);
	vals[0] = try_open(DESC"maps.inf");
	vals[1] = read(vals[0], buff, 2047);
	buff[vals[1]] = '\0';
	vals[2] = ft_atoi(buff);
	close(vals[0]);
	if (mapid >= vals[2] || mapid < 0)
		ft_exit(NULL);
	vals[1] = 0;
	ptr = buff;
	while (ptr && vals[1] <= vals[2] && vals[1] <= mapid)
	{
		if (!*ptr)
			ft_exit(NULL);
		ptr = ft_strchr(ptr, '\n') + 1;
		vals[1]++;
	}
	read_inf(ptr, map);
	ft_strdel(&buff);
}
