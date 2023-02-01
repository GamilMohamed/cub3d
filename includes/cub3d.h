/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:33:03 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/01 04:44:24 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
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

# define ERR_NO_MAP "where is the map bro ?"
# define ERR_CHARS "no direction or strange char found!"
# define ERR_INVALID "invalid map!"
# define ERR_KEYS "invalid keys!"
# define ERR_FDFAIL "open file failed!"
# define SIZE 2

typedef struct s_rr		t_rr;
typedef struct t_map	t_map;
typedef struct t_mlx	t_mlx;

typedef struct t_map
{
	char				*cubfile;
	char				**map;
	int					filefd;
	int					maxlen;
	int					height;
	char				*colors[2];
	int					type_colors[2];
	int					type_path[4];
	char				*path[4];
	t_mlx				*mlx;
}						t_map;

typedef struct t_mlx
{
	void	*mlx;
	void	*win;
}		t_mlx;

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
char					*readinfo(t_map *map, int *fd, char *str);
char					*readmap(t_map *map);
//fill.c
int						fillpathcolors(t_map *map, char *str, int index);
int						filldirections(t_map *map, char **tab);
void					*fillstruct(t_map *map);
/*		misc			*/
//error.c
int						ft_error(char *str, char *color, t_map *map);
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

int						ft_game(t_map *map, t_mlx *mlx);

#endif