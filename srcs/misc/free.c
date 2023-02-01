/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:33:17 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/01 17:51:29 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_freestruct_map(t_map *map)
{
	if (!map)
		return (NULL);
	ft_free((void **)& map->cubfile);
	int i = -1;
	while (++i < 4)
		ft_free((void **)& map->path[i]);
	// ft_freerr(map->files);
	// map->files = 0;
	return (NULL);
}