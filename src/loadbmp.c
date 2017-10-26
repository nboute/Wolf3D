/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadbmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:11:00 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 22:45:40 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitmap.h"
#include "../inc/header.h"
#include <stdlib.h>

void				read_data(int fd, t_bmp_hd *head, t_bmp_if *inf)
{
	int				ret;
	char			*buff;

	buff = (char*)malloc(sizeof(char) * 41);
	if ((ret = read(fd, buff, 14)) != 14)
		ft_exit(NULL);
	head->type = *(unsigned short*)buff;
	head->size = *(unsigned int*)(buff + 2);
	head->res1 = *(unsigned short*)(buff + 6);
	head->res1 = *(unsigned short*)(buff + 8);
	if ((ret = read(fd, buff, 40)) != 40)
		ft_exit(NULL);
	inf->size = *(unsigned int*)(buff);
	inf->height = *(int*)(buff + 4);
	inf->width = *(int*)(buff + 8);
	inf->planes = *(unsigned short*)(buff + 12);
	inf->bits = *(unsigned short*)(buff + 14);
	inf->compression = *(unsigned int*)(buff + 16);
	inf->imgsize = *(unsigned int*)(buff + 20);
	inf->xres = *(int*)(buff + 24);
	inf->yres = *(int*)(buff + 28);
	inf->nbcols = *(unsigned int*)(buff + 32);
	inf->impcols = *(unsigned int*)(buff + 36);
	ft_strdel(&buff);
}

int					**get_texture(int fd, int **texture, t_bmp_if *inf)
{
	char			*buff;
	unsigned int	i;
	int				x;
	int				y;

	i = 14 + 40 + 4 * inf->nbcols;
	y = 0;
	while (y < inf->width)
		if (!(texture[y++] = (int*)malloc(sizeof(int) * inf->height)))
			ft_exit(NULL);
	y = inf->width;
	if (!(buff = (char*)malloc(((inf->bits / 8) * (inf->height) + 1))))
		ft_exit(NULL);
	while (--y >= 0 && i < inf->imgsize)
	{
		x = -1;
		if ((read(fd, buff, (inf->bits * inf->height) / 8)) <= 0)
			ft_exit(NULL);
		while (++x < inf->height)
			texture[y][x] = (buff[x * 3] + (buff[x * 3 + 1] << 8) +
					(buff[x * 3 + 2] << 16)) & 0x00FFFFFF;
		i += inf->width * 3;
	}
	ft_strdel(&buff);
	return (texture);
}

int					**bmp_to_array(char *name, int width, int height)
{
	int				fd;
	char			*buff;
	t_bmp_hd		head;
	t_bmp_if		inf;
	int				**texture;

	if ((fd = open(name, O_RDONLY)) <= 1)
		ft_exit(NULL);
	read_data(fd, &head, &inf);
	if (!(buff = malloc(sizeof(char) * (4 * inf.nbcols + 1))))
		ft_exit(NULL);
	if (inf.nbcols)
		read(fd, buff, 4 * inf.nbcols);
	if (!(texture = (int**)malloc(sizeof(int*) * inf.width)))
		ft_exit(NULL);
	ft_strdel(&buff);
	texture = get_texture(fd, texture, &inf);
	if (inf.width != width || inf.height != height || !texture)
		ft_exit(NULL);
	return (texture);
}
