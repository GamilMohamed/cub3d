/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:33:03 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/16 02:47:32 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SPACES " \t"
# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define ESCAPE 65307

# define ERR_NO_MAP "where is the map bro ?"
# define ERR_CHARS "no direction or strange char found!"
# define ERR_INVALID "invalid map!"
# define ERR_KEYS "invalid keys!"
# define ERR_FDFAIL "open file failed!"
# define ERR_MAP "map has leaks"

# define SIZE 1

# define WIDTH 960
# define HEIGHT 540

# define WIDTH_2 480
# define HEIGHT_2 270

#define WIDTH_4 240
#define HEIGHT_4 135

# define W 119
# define A 97
# define S 115
# define D 100

# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

typedef struct s_rr		t_rr;
typedef struct t_map	t_map;
typedef struct t_mlx	t_mlx;
typedef struct t_data	t_data;
typedef struct t_press	t_press;
typedef struct t_sprite	t_sprite;


typedef double t_luno2f	__attribute__((ext_vector_type(2)));
typedef int t_luno2i	__attribute__((ext_vector_type(2)));


typedef struct	t_sprite
{
	t_luno2f	sprite;
	t_luno2f	sprite_pos;
	t_luno2i	ds;
	t_luno2i	de;
	t_luno2f	transform;
	int			z;
	double		invdet;
	int			spritescreen;
	int			vmove_s;
	int			sprite_h;
	int			sprite_w;
	t_luno2i	tex;
	// int			texX;
	int			k;
	// int			texY;
	int			color;
	int			i;
	int			d;
}				t_sprite;

typedef struct t_drawrays
{
	double				pwall;
	int					lineh;
	int					texnum;
	t_luno2i			tex;
	t_luno2i			draw;
	double				texpos;
	unsigned int					color;
	int					y;
	double				step;
	double				wallx;

}						t_drawrays;

typedef struct s_help
{
	void				*img;
	void				*help;
	int					*data;
	int					*addr;

	int					size_l;
	int					bpp;
	int					endian;
	int					w;
	int					h;
	int					**help_buff;
}						t_help;

typedef struct s_img
{
	void				*img;
	int					*data;
	int					size_l;
	int					bpp;
	int					endian;
	int					w;
	int					h;
}						t_img;

typedef struct t_press
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
	int					up;
	int					down;
	int					esc;
	int					q;
	int					z;
	int					m;
	int					mouse;
	int					mouse_x;
	int					mouse_y;
	int					door;
	int					h;
}						t_press;

typedef struct s_plane
{
	t_luno2f			camera;
	t_luno2i			map;
	t_luno2f			pos;
	t_luno2f			raydir;
	t_luno2f			dir;
	t_luno2f			plane;
	t_luno2f			deltadist;
	int					side;
	t_luno2f			step;
	t_luno2f			sdist;
	int					hit;
	double				drawstart;
	double				drawend;
	double				movespeed;
	double				rotspeed;
	int					buff[HEIGHT][WIDTH];
	int					**texture;
	int					re_buf;
	int					door;
	char				clock[64][1024];
	int					**tex_clock;
	double				tex_buff[WIDTH];
	double				sprite_dist[64];
	int					sprite_ordr[64];
}						t_plane;

typedef struct s_temp
{
	t_map				*map;
	void				*win;
	void				*img;
	char				*addr;
	int					a;
	int					b;
	int					c;
	int					height;
	int					width;
	double				size;
	t_luno2f			endray[3];
	t_luno2f			coords;
	t_luno2f			plane[2];
	t_luno2f			front;
}						t_temp;

typedef struct t_map
{
	t_luno2f			pos;
	void				*addr;
	int					nbrayons;
	char				*cubfile;
	char				**map;
	int					filefd;
	int					maxlen;
	int					height;
	char				*colors[2];
	int					ceiling[3];
	int					floor[3];
	int					type_colors[2];
	int					type_path[4];
	char				*path[4];
	char				last;
	t_temp				*mini;
	t_temp				*temp;
	int					size;
	t_mlx				*mlx;
	t_data				*data;
	t_plane				*plane;
	double				rotation;
	t_press				*press;
	t_img				img;
	t_help				help;
}						t_map;

typedef struct t_mlx
{
	void				*mlx;
	void				*win;
	void				*bg;
	t_data				*data;
}						t_mlx;

typedef struct t_data
{
	t_luno2f			player_pos;
	double				pos_px;
	double				pos_py;
	double				pos_cx;
	double				pos_cy;
	char				player;
	int					win_h;
	int					win_w;
	char				*bg;
	void				*back;
	t_mlx				*mlx;

}						t_data;

/*		parsing			*/
// args.c
int						checkextension(int ac, char *str);
// split.c
char					**ft_specialit(char const *s, char *charset, int size);
// map.c
int						checkaround(t_map *map, int x, int y, char **tab);
void					check_surroundings(t_map *map);
void					checkchars(t_map *map);
void					checkmap(t_map *map);
//read.c
int						lineempty(char *buff);
// char					*readinfo(t_map *map, int *fd, char *str);
char					*readinfo(t_map *map, int *fd, const char *str);

char					*readmap(t_map *map);
//fill.c
int						fillpathcolors(t_map *map, char *str, int index);
int						filldirections(t_map *map, char **tab);
void					*fillstruct(t_map *map);
/*		misc			*/
//error.c
void					*ft_error(char *str, char *color, t_map *map);
// int						ft_error(char *str, char *color, t_map *map);
void					*closefile(t_map *map);
//free.c
void					*ft_freestruct_map(t_map *map);
//print.c
void					ft_printmap(char **tab, int value);
char					*c(int n);
//chainedlist.c
int						ft_lstadd_back_rr(t_rr **lst, t_rr *var);
t_rr					*ft_lstnew_rr(char *name, int type);
void					ft_freerr(t_rr *node);
void					ft_printlist(t_rr *temp);
// void	ft_stoval(char *str, int n, int len);
void	ft_stoval(char *str, int n, int start, int len);

int	lenof(int n);
void	my_pixel_put(t_help *help, unsigned int x, unsigned int y,
		unsigned int color);
ssize_t	mlx_get_pixel(t_help *help, unsigned int x, unsigned int y);
/*	game	*/
// init.c
// int						initmlx(t_map *map, t_mlx *mlx, t_data *data,
// t_temp *temp);
int						initmlx(t_map *map, t_mlx *mlx);

void					init_plane(t_plane *plane, t_map *map);
void					init_buff(t_plane *p);

// color.c
int						create_rgb(int t, int a, int b, int c);
int						create_trgb(int tab[3]);
void					backgroundcolor(t_map *map, t_mlx *mlx, t_data *data,
							t_temp *temp);

// raycasting.c
void					draw_rayons(t_temp *tmp, t_luno2f coords, t_map *map);
// void					draw_rayons_all(t_map *map, t_plane *p);
// void					draw_rayons_all_2(t_map *map, t_drawrays *r, t_plane *p,
							// int i, int max);
// void					draw_rayons_all(t_map *map, t_plane *p, int max);
void	draw_rayons_all_2(t_map *map, t_drawrays *r, t_plane *p, int i, int max, int time);
void	draw_rayons_all(t_map *map, t_plane *p, int max, int time);


// calc.c
t_luno2i				convert_d_to_i(t_luno2f src);
t_luno2f				calc_rotation(t_luno2f coords, int r, double rad,
							int m);
double					calc_radius(double angle);
t_luno2f				normalize(t_luno2f coords);

// move.c
int						key_release(int keycode, t_map *map);
int						key_press(int keycode, t_map *map);
int						move(t_map *map);

// game.c
void					printcoords(t_luno2i val, t_luno2f val2);
void					destroywindows(t_mlx *mlx, t_map *map);

int						ft_game(t_map *map, t_mlx *mlx, t_data *data);

// draw.c
int						condition(int x, int y, int size, t_map *map);
void					draw_circle(t_temp *tmp, t_luno2f coords, int r);
t_luno2f				draw_line_rays(t_map *map, t_luno2f end,
							t_luno2f coords, bool print);
int						load_image(t_map *map, int *texture, char *path,
							t_img *img);

void					draw(t_map *map);
void					load_texture(t_map *map);

// void	my_mlx_pixel_put(t_temp temp, int x, int y, int color);
// void	pixel(t_temp temp, t_luno2f coords, int color);

void					my_mlx_pixel_put(t_temp *mp, int x, int y, int color);
t_luno2f				docircle(t_temp *temp, t_luno2f coords, int ray);
void					pixel(t_temp *temp, t_luno2f coords, int color);
void					camera_rays(t_temp *tmp, t_map *map, t_luno2f coords,
							double size);

// minimap.c
void					map_to_minimap(t_map *map, t_data *data, t_temp *temp,
							int size);
// void	map_to_minimap(t_map *map, t_data *data, t_temp temp, int size);

void					camera_rays(t_temp *tmp, t_map *map, t_luno2f coords,
							double size);
void					init_minimap(t_map *map, t_mlx *mlx, t_data *data);
void					fill_minimap(t_map *map, t_mlx *mlx, t_data *data);
void					orientation_player(t_plane *plane, char player);

void					camera_plane(t_map *map, t_plane *p, int x);
void					print_to_map(t_map *map);
void					init_cast(t_plane *plane, int index);

void					draw(t_map *map);

// utils.c
double					sides(t_plane *p);
t_luno2i				get_draw(int lineh);
int						get_tex_x(t_plane *p, double wallx);
void					wall_color(t_plane *p, unsigned int *color, t_luno2i tex, int time);

// void					wall_color(t_plane *p, int *color, t_luno2i tex, int time);
double					get_wall_x(t_plane *p, double pwall);

// void					print_help(t_map *map);
void	print_help(t_map *map, t_help *help);

void	init_sprite(t_map *map, t_drawrays *r, t_plane *p, int time);
#endif