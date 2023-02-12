/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:06:31 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/12 20:34:25 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_error(char *str, char *color, t_map *map)
{
	ft_printf("%s%s%s\n", color, str, RESET);
	closefile(map);
	exit (1);
}

void	*closefile(t_map *map)
{
	if (!map)
		return (NULL);
	get_next_line(1, 1);
	close(map->filefd);
	ft_freestruct_map(map);
	return (NULL);
}
