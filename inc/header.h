/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:45:11 by nboute            #+#    #+#             */
/*   Updated: 2017/07/11 15:18:53 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
typedef struct	s_keys
{
	short		key;
	short		pressed;
}				t_keys;

typedef struct	s_vects
{
	double		posX;
	double		posY;
	double		planeX;
	double		planeY;
	double		camX;
	double		rayposX;
	double		rayposY;
	double		raydirX;
	double		raydirY;
	double		dirX;
	double		dirY;
	int			mapX;
	int			mapY;
	double		sidedistY;
	double		sidedistX;
	double		deltadistX;
	double		deltadistY;
	double		perpwalldist;
	int			stepX;
	int			stepY;
}				t_vects;

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
	double		startx;
	double		starty;
	int			out;
}				t_map;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int			height;
	int			width;
	char		*data;
	int			bpx;
	int			size;
	int			endian;
	t_map		*map;
	int			mapwid;
	int			maphei;
	t_vects		*vectors;
	t_keys		*keys;
	int			***textures;
	double		movespeed;
	double		rotspeed;
}				t_mlx;

t_map	*mazegen(t_map *maze, int	size, int out);
int		print_grid(t_map *maze, int mx, int my);

#endif
