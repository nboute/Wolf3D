/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:45:11 by nboute            #+#    #+#             */
/*   Updated: 2017/07/13 14:45:56 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <pthread.h>
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
typedef struct	s_keys
{
	short		key;
	short		pressed;
}				t_keys;

typedef struct	s_thread
{
	int			id;
	void		*data;
	pthread_t	thread;
}				t_thread;

typedef struct	s_cam
{
	double		posX;
	double		posY;
	double		planeX;
	double		planeY;
	double		dirX;
	double		dirY;
}				t_cam;

typedef struct	s_vects
{
	double		camX;
	double		rayposX;
	double		rayposY;
	double		raydirX;
	double		raydirY;
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
	int			end;
	t_map		*map;
	int			mapwid;
	int			maphei;
	t_vects		vectors[8];
	t_cam		cam;
	t_keys		*keys;
	int			***textures;
	double		movespeed;
	double		rotspeed;
}				t_mlx;

t_map	*mazegen(t_map *maze, int	size, int out);
int		print_grid(t_map *maze, int mx, int my);
int		**bmp_to_array(char *name, int width, int height);

#endif
