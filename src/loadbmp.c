/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadbmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:11:00 by nboute            #+#    #+#             */
/*   Updated: 2017/10/08 17:27:34 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitmap.h"
#include "../inc/header.h"
#include <stdlib.h>
#include <stdio.h>

int		**bmp_to_array(char *name, int width, int height)
{
	int	fd;
	int	ret;
	char	*buff;
	t_bmp_hd	head;
	t_bmp_if	inf;
	int		**texture;

	ft_putendl(name);
	if ((fd = open(name, O_RDONLY)) <= 1)
		ft_exit(NULL);
	buff = (char*)malloc(sizeof(char) * 41);
	ret = read(fd, buff, 14);
	head.type = *(unsigned short*)buff;
	head.size = *(unsigned int*)(buff + 2);
	head.res1 = *(unsigned short*)(buff + 6);
	head.res1 = *(unsigned short*)(buff + 8);
	ret = read(fd, buff, 40);
	inf.size = *(unsigned int*)(buff);
	inf.height = *(int*)(buff + 4);
	inf.width = *(int*)(buff + 8);
	inf.planes = *(unsigned short*)(buff + 12);
	inf.bits = *(unsigned short*)(buff + 14);
	inf.compression = *(unsigned int*)(buff + 16);
	inf.imgsize = *(unsigned int*)(buff + 20);
	inf.xres = *(int*)(buff + 24);
	inf.yres = *(int*)(buff + 28);
	inf.nbcols = *(unsigned int*)(buff + 32);
	inf.impcols = *(unsigned int*)(buff + 36);

	width = 0;
	height = 0;
	if (!(texture = (int**)malloc(sizeof(int*) * inf.width)))
		ft_exit(NULL);
	if (buff)
		free(buff);
	if (!(buff = malloc(sizeof(char) * (4 * inf.nbcols+ 1))))
		ft_exit(NULL);
	if (inf.nbcols)
		ret = read(fd, buff, 4 * inf.nbcols);
	//parse_colors;
	free(buff);
	unsigned int	i;
	int	x;
	int	y;
	i = 14 + 40 + 4 * inf.nbcols;
	y = 0;
	while (y < inf.width)
		if (!(texture[y++] = (int*)malloc(sizeof(int) * inf.height)))
			ft_exit(NULL);
	y = inf.width;
	if (!(buff = (char*)malloc(sizeof(char) * ((inf.bits / 8) * (inf.height) + 1))))
		ft_exit(NULL);
//	printf("loading texture of width %d and height %d\n", inf.width, inf.height);
	ft_putendl(name);
	while (y && i < inf.imgsize)
	{
		y--;
		x = 0;
		int	k;
		k = (inf.bits / 8 * inf.height);
	//	if (k % 4)
	//		k += 4 - (k % 4);
		ret = read(fd, buff, k);
		buff[ret] = '\0';
		while (x < inf.height)
		{
			texture[y][x] = (buff[x * 3] + (buff[x * 3 + 1] << 8) +
					(buff[x * 3 + 2] << 16)) & 0x00FFFFFF;
			x++;
		}
		i += inf.width * 3;
	}
	ret = read(fd, buff, inf.height * inf.bits / 8);
	buff[ret] = '\0';
//	printf("\n%s loaded in %p\n", name, texture);
	return (texture);
}
