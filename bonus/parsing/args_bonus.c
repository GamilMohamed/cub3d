/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:03:55 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/12 20:49:20 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	checkextension(int ac, char *str)
{
	if (ac != 2)
		return (ft_error("./cub3d [path_to_map.cub]\n", RED, NULL), 1);
	if (ft_strlen(ft_strnstr(str, ".cub", ft_strlen(str))) != 4)
		return (ft_error("extension should be .cub\n", YELLOW, NULL), 1);
	return (0);
}
