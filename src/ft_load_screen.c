/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 20:07:40 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 20:33:55 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include "../inc/bitmap.h"

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

void		ft_mix_pixel(t_mlx *mlx, int i[2], int color, int perc)
{
	int		col2;

	col2 = *(unsigned*)(mlx->data + (i[0] + 400) * mlx->size + 4 * i[1]);
	ft_place_pixel(ft_gradation(col2, color, perc) & 0x00FFFFFF,
		i[1], i[0] + 400, mlx);
}

void		destroy_screen(int ***text)
{
	int	i;

	i = 0;
	if (text)
	{
		if (*text)
		{
			while (i < 200)
			{
				if ((*text)[i])
					free((*text)[i]);
				i++;
			}
			free(*text);
		}
	}
}

void		ft_load_screen(t_mlx *mlx)
{
	int		**text;
	int		i[2];
	int		col;

	mlx->loading = 1;
	if (!(text = bmp_to_array(TEXTURES"youdied_v2.bmp", 200, 1200)))
		ft_exit(NULL);
	i[0] = -1;
	while (++i[0] < 200)
	{
		i[1] = -1;
		while (++i[1] < 1200)
		{
			col = text[i[0]][i[1]];
			if (i[0] < 30)
				ft_mix_pixel(mlx, i, text[i[0]][i[1]], i[0] * 3 + 10);
			else if (i[0] >= 170)
				ft_mix_pixel(mlx, i, text[i[0]][i[1]],
						(abs(200 - i[0])) * 3 + 10);
			else
				ft_place_pixel(text[i[0]][i[1]], i[1], i[0] + 400, mlx);
		}
	}
	destroy_screen(&text);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
