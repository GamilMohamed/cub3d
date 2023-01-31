/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:03:55 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/30 16:46:17 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checkextension(int ac, char *str)
{
	if (ac != 2)
		return (ft_error("./cub3d [path_to_map.cub]\n", RED, NULL));
	if (ft_strlen(ft_strnstr(str, ".cub", ft_strlen(str))) != 4)
		return (ft_error("extension should be .cub\n", YELLOW, NULL));
	return (0);
}
