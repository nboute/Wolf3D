/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadbmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:11:00 by nboute            #+#    #+#             */
/*   Updated: 2017/07/15 17:42:05 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bitmap.h"
#include <stdlib.h>
#include <stdio.h>

int		**bmp_to_array(char *name, int width, int height)
{
	int	fd;
	int	ret;
	char	*buff;
	t_bmp_hd	head;
	t_bmp_if	inf;

	if ((fd = open(name, O_RDONLY)) <= 1)
		return (NULL);
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

	int	**texture = (int**)malloc(sizeof(int*) * inf.width);
	free(buff);
	buff = malloc(sizeof(char) * (4 * inf.nbcols+ 1));
	if (inf.nbcols)
		ret = read(fd, buff, 4 * inf.nbcols);
	//parse_colors;
	free(buff);
	buff = malloc(sizeof(char) * 4 * (inf.width + 1));
	unsigned int	i;
	int	x;
	int	y;
	i = 14 + 40 + 4 * inf.nbcols;
	x = 0;
	while (x < inf.height)
	{
		texture[x++] = (int*)malloc(sizeof(int) * inf.height);
	}
	x = inf.height;
	free(buff);
	width = 64;
	height = 64;
	printf("\n%s\n", name);
	while (x && i < inf.imgsize)
	{
		x--;
		y = 0;
		int	k;
		k = (inf.bits / 8 * inf.height);
		if (k % 4)
			k += 4 - (k % 4);
		buff = (char*)malloc(sizeof(char) * (inf.bits / 8) * (inf.height + 1));
		ret = read(fd, buff, k);
		buff[ret] = '\0';
		while (y < inf.height)
		{
			texture[y][x] = (buff[y * 3] + (buff[y * 3 + 1] << 8) + (buff[y * 3 + 2] << 16)) & 0x00FFFFFF;
			printf("%#X ", texture[y][x]);
			y++;
		}
		i += inf.width;
	}
	ret = read(fd, buff, inf.width * inf.bits / 8);
	buff[ret] = '\0';
	printf("[%d]\n", ret);
	return (texture);
}
