/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:14:34 by nboute            #+#    #+#             */
/*   Updated: 2017/09/18 17:43:40 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

#include <unistd.h>
#include <fcntl.h>
# define TEXT_PATH "~/Projets/Github/Wolf3D/textures/"
# define BUF_SIZE 64

typedef struct		s_bmp_hd
{
	int				type;
	int				size;
	int				res1;
	int					res2;
	int				offset;
}					t_bmp_hd;

typedef struct		s_bmp_if
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short int	planes;
	unsigned short	int bits;
	unsigned int		compression;
	unsigned int		imgsize;
	int					xres;
	int					yres;
	unsigned int		nbcols;
	unsigned int		impcols;
}					t_bmp_if;

int		**bmp_to_array(char *name, int width, int height);

#endif
