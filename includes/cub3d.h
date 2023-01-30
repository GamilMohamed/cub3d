/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:33:03 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/30 02:20:53 by mgamil           ###   ########.fr       */
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
# define RESET "\001\033[0m\002"
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define WHITE "\001\033[0;37m\002"

typedef struct s_rr	t_rr;

typedef struct t_map
{
	char			*cubfile;
	char			*colors[2];
	t_rr			*files;
}					t_map;

typedef struct s_rr
{
	char			*name;
	int				type;
	struct s_rr		*next;
}					t_rr;

/*		parsing			*/
// args.c
int					checkextension(int ac, char *str);
/*		misc			*/
//error.c
int					ft_error(char *str, char *color);
//chainedlist.c
int					ft_lstadd_back_rr(t_rr **lst, t_rr *var);
t_rr				*ft_lstnew_rr(char *name, int type);
void				ft_freerr(t_rr *node);
void				ft_printlist(t_rr *temp);

#endif