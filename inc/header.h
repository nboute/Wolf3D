/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:45:11 by nboute            #+#    #+#             */
/*   Updated: 2017/10/26 16:37:37 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <pthread.h>
# include <time.h>
# define RAYCAST_THREADS 1
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define TEXWID 64
# define TEXHEI 64
# define PI 3.14159265359
# define ABS(x) (x < 0) ? -x : x
# define TEXTURES "/Users/nboute/Projets/Github/Wolf3D/textures/"
# define DESC "/Users/nboute/Projets/Github/Wolf3D/desc/"
# define BASE_HExA "0123456789ABCDEF"
typedef struct	s_keys
{
	short		key;
	short		pressed;
}				t_keys;

typedef struct			s_point
{
	int					x;
	int					y;
	int					color;
}						t_point;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_sprtex
{
	int			**text;
	int			alpha;
}				t_sprtex;

typedef struct	s_thread
{
	int			id;
	void		*data;
	pthread_t	thread;
}				t_thread;

typedef struct	s_cam
{
	double		posx;
	double		posy;
	double		planex;
	double		planey;
	double		dirx;
	double		diry;
	char		target;
}				t_cam;

typedef struct	s_vects
{
	int			x;
	double		camx;
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedisty;
	double		sidedistx;
	double		deltadistx;
	double		deltadisty;
	double		pwalldt;
	int			stepx;
	int			stepy;
	int			side;
	double		wallx;
	double		drawstart;
	double		drawend;
	int			drawstartx;
	int			drawstarty;
	int			drawendx;
	int			drawendy;
	int			lineh;
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
	t_sprtex	*sprtex;
	int			*spralphas;
	int			nbsprites;
	int			nbspr;
	int			nbwalls;
	int			***walls;
	int			nbfloors;
	int			***floors;
	int			out;
	int			hit;
}				t_map;

typedef struct	s_mazedata
{
	int			***arrow;
	int			exit[2];
	short		hp;
}				t_mazedata;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int			height;
	int			width;
	char		*data;
	char		*imgdata;
	int			bpx;
	int			size;
	int			end;
	t_map		*map;
	int			mapwid;
	int			maphei;
	t_vects		vectors[8];
	t_cam		cam;
	t_keys		keys[4];
	double		movespeed;
	double		rotspeed;
	double		zbuff[1200];
	short		arrowdir;
	short		loading;
	void		*mapdata;
	clock_t		time;
	clock_t		oldtime;
	double		frametime;
}				t_mlx;

t_map			*mazegen(int	size, int out);
int				print_grid(t_map *maze, int mx, int my);
t_map			*slidegen(int width, int height);
t_map			*ft_start_map();
t_map			*load_map(int id, t_map **oldmap, t_mlx *mlx);
int				ft_exit(void *ret);
void			ft_place_pixel(int color, int x, int y, t_mlx *mlx);
void			ft_load_screen(t_mlx *mlx);
int				**ft_rotate_2d(int **src, int size, int angle);
t_mazedata		*ft_getmazedata(t_mlx *mlx);
void			get_map_textures(unsigned short mapId, t_map *map);
void			load_textures(char **textnames, t_map *map, int *spralphas);
t_map			*new_map(void);
int				key_released(int key, void *ptr);
int				mouse_pressed(int button, int x, int y, void *data);
int				key_pressed(int key, void *ptr);
void			rotate_view(double rotspeed, t_mlx *mlx);
void			ft_move(t_mlx *mlx, char **map);
void			ft_draw_arrow(t_mlx *mlx);
void			*raycast(void	*data);
void			ft_combsort(int *order, double *dist, int amount);
t_sprite		*add_sprite(t_map *map, int	texNum, double x, double y);
void			ft_threads(t_mlx *mlx);
int				looper(void *ptr);
void			ft_move_mobs(t_mlx *mlx);
void			ft_map_fct(t_mlx *mlx);
int				free_map(t_map *map);
int				**bmp_to_array(char *name, int width, int height);
int				***ft_arrow(void);
t_mlx			*init_mlx(t_mlx *ptr);
void		create_maze(t_map *maze, int oldpos, int movey, int movex);

#endif
