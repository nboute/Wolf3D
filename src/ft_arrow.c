/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:48:25 by nboute            #+#    #+#             */
/*   Updated: 2017/10/16 15:53:56 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_invert_rows_square_2d_matrix(int **dest, int **src, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dest[i][j] = src[i][size -j -1];
			j++;
		}
		i++;
	}
}

void	ft_transpose_square_2d_matrix(int **dest, int **src, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dest[j][i] = src[i][j];
			j++;
		}
		i++;
	}
}

void	ft_invert_cols_square_2d_matrix(int **dest, int **src, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dest[i][j] = src[size - i - 1][j];
			j++;
		}
		i++;
	}
}

int		ft_rot_p2(int **dest, int **src, int size, int angle)
{
	if (angle == 90)
		ft_invert_rows_square_2d_matrix(dest, src, size);
	else if (angle == 180 || angle == 270)
		ft_invert_cols_square_2d_matrix(dest, src, size);
	return (0);
}

int		**ft_rotate_2d(int **src, int size, int angle)
{
	int	i;
	int	**dest;
	int	**tmp;

	i = -1;
	if (!(dest = (int**)malloc(sizeof(int*) * size)))
		ft_exit(NULL);
	if (!(tmp = (int**)malloc(sizeof(int*) * size)))
		ft_exit(NULL);
	while (++i < size)
	{
		if (!(tmp[i] = (int*)malloc(sizeof(int) * size)) || 
				!(dest[i] = (int*)malloc(sizeof(int) * size)))
			ft_exit(NULL);
	}
	if (angle == 90)
		ft_transpose_square_2d_matrix(tmp, src, size);
	else if (angle == 180)
		ft_invert_rows_square_2d_matrix(tmp, src, size);
	else if (angle == 270)
		ft_transpose_square_2d_matrix(tmp, src, size);
	ft_rot_p2(dest, tmp, size, angle);
	return (dest);
}
