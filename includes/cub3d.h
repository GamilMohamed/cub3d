/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:33:03 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/11 21:20:09 by mgamil           ###   ########.fr       */
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

# define SIZE 1

# define WIDTH 960
# define HEIGHT 540

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

typedef double			t_luno2f	__attribute__((ext_vector_type(2)));
typedef int				t_luno2i	__attribute__((ext_vector_type(2)));

typedef struct t_drawrays
{
	double				pwall;
	int					lineh;
	int					texnum;
	t_luno2i			tex;
	t_luno2i			draw;
	double				texpos;
	int					color;
	int					y;
	double				step;
	double				wallx;

}						t_drawrays;

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
	int					mouse;
	int					mouse_x;
	int					mouse_y;
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
	double				movespeed;
	double				rotspeed;
	int					buff[540][960];
	int					**texture;
	int					re_buf;
}						t_plane;

typedef struct s_temp
{
	t_map				*map;
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
void	*ft_error(char *str, char *color, t_map *map);
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
void					draw_rayons_all(t_map *map, t_plane *p);

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
void					load_image(t_map *map, int *texture, char *path,
							t_img *img);
void					draw(t_map *map);
void					load_texture(t_map *map);

void					my_mlx_pixel_put(t_temp *mp, int x, int y, int color);
t_luno2f				docircle(t_temp *temp, t_luno2f coords, int ray);
void					pixel(t_temp *temp, t_luno2f coords, int color);
void					camera_rays(t_temp *tmp, t_map *map, t_luno2f coords,
							double size);

// minimap.c
void					map_to_minimap(t_map *map, t_data *data, t_temp *temp,
							int size);
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
void					wall_color(t_plane *p, int *color, t_luno2i tex);
double					get_wall_x(t_plane *p, double pwall);

#endif