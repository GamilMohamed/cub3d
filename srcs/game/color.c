/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:08:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/06 13:38:16 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int t, int a, int b, int c)
{
	return (a << 24 | b << 16 | c << 8 | 255);
}

int	create_trgb(int tab[3])
{
	return (tab[0] << 24 | tab[1] << 16 | tab[2] << 8 | 255);
}

void	backgroundcolor(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{
	int	i;
	int	j;
	int	ceiling;
	int	floor;

	i = -1;
	ceiling = create_trgb(map->ceiling);
	floor = create_trgb(map->floor);
	while (++i < data->win_w)
	{
		j = -1;
		while (++j < data->win_h)
		{
			if (j < data->win_h / 2 && j < data->win_w / 2)
				my_mlx_pixel_put(temp, i, j, ceiling);
			else
				my_mlx_pixel_put(temp, i, j, floor);
		}
	}
}
