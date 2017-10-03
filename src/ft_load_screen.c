/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 20:07:40 by nboute            #+#    #+#             */
/*   Updated: 2017/09/28 15:43:40 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../inc/bitmap.h"

#include <stdio.h>
int			ft_gradation(unsigned int col, unsigned int col2, int p)
{
	int		r;
	int		g;
	int		b;

	r = ((col2 >> 16) & 0x000000FF) - ((col >> 16) & 0x000000FF);
	g = ((col2 >> 8) & 0x000000FF) - ((col >> 8) & 0x000000FF);
	b = (col2 & 0x000000FF) - (col & 0x000000FF);
	r = (r * p) / 100;
	g = (g * p) / 100;
	b = (b * p) / 100;
	return (col + r * 65536 + g * 256 + b);
}

int	ft_mix_pixel(t_mlx *mlx, int x, int y, int color, int perc)
{
	int	col2;

	col2 = *(unsigned*)(mlx->data + y * mlx->size + 4 * x);
	ft_place_pixel((ft_gradation(col2, color, perc) & 0x00FFFFFF), x, y, mlx);
	return (0);
}


void	ft_load_screen(t_mlx *mlx)
{
	int	**text;
	int	i;
	int	j;
	int	col;

	ft_putendl("loading map");
	mlx->loading = 1;
	text = bmp_to_array(TEXT_PATH"youdied_v2.bmp", 200, 1200);
	j = 0;
	while (j < 200)
	{
		i = 0;
		while (i < 1200)
		{
			col = text[j][i];
			if (j < 30)
				ft_mix_pixel(mlx, i, j + 400, text[j][i], j * 3 + 10);
			else if (j >= 170)
				ft_mix_pixel(mlx, i, j + 400, text[j][i], (abs(200 - j)) * 3 + 10);
			else
				ft_place_pixel(text[j][i], i, j + 400, mlx);
			i++;
		}
		j++;
	}
//	ft_fast_memcpy(mlx->imgdata, mlx->data, mlx->bpx / 8 * mlx->height * mlx->width);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_putendl("it should have worked here lul");
}
