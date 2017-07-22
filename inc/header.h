/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:45:11 by nboute            #+#    #+#             */
/*   Updated: 2017/07/22 19:30:25 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <pthread.h>
# define RAYCAST_THREADS 1
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define TEXT_PATH "/Users/nboute/Projets/Github/Wolf3D/textures/"
# define TEXWID 64
# define TEXHEI 64
# define PI 3.14159265359

typedef struct	s_keys
{
	short		key;
	short		pressed;
}				t_keys;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_thread
{
	int			id;
	void		*data;
	pthread_t	thread;
}				t_thread;

typedef struct	s_sprinf
{
	double		sprX;
	double		sprY;
	double		invDet;
	double		transfX;
	double		transfY;
	int			sprscreenX;
	int			sprHeight;
	int			sprWidth;
	int			sprid;
	int			*sprOrd;
	double		*sprDist;
}				t_sprinf;

typedef struct	s_flrinf
{
	double		distWall;
	double		distPlayer;
	double		currDist;
	double		weight;
	double		currFlrX;
	double		currFlrY;
	int			flrTexX;
	int			flrTexY;
}				t_flrinf;

typedef struct	s_cam
{
	double		posX;
	double		posY;
	double		planeX;
	double		planeY;
	double		dirX;
	double		dirY;
	char		target;
}				t_cam;

typedef struct	s_vects
{
	int			x;
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
	double		pwalldt;
	int			stepX;
	int			stepY;
	int			side;
	double		wallX;
	double		drawstart;
	double		drawend;
	int			drawstartX;
	int			drawstartY;
	int			drawendX;
	int			drawendY;
	int			lineH;
}				t_vects;

typedef struct	s_map
{
	short		id;
	char		**map;
	int			width;
	int			height;
	double		startx;
	double		starty;
	int			***textures;
	int			nbtextures;
	t_sprite	*sprites;
	int			nbsprites;
	int			out;
	int			hit;

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
	double		movespeed;
	double		rotspeed;
	double		zbuff[1200];
	short		loading;
}				t_mlx;

t_map	*mazegen(int	size, int out);
int		print_grid(t_map *maze, int mx, int my);
int		**bmp_to_array(char *name, int width, int height);
t_map	*slidegen(int width, int height, int density);
t_map	*ft_start_map();
t_map	*load_map(int id, t_map **oldmap, t_mlx *mlx);

#endif
