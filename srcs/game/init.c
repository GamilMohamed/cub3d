/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:01:09 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/10 17:50:51 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initmlx(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	data->win_h = 540;
	data->win_w = 960;
	// mlx_get_screen_size(mlx->mlx, &data->win_w, &data->win_h);
	mlx->win = mlx_new_window(mlx->mlx, data->win_w, data->win_h, "cub3D");
	if (!mlx->win)
		return (ft_free((void **)&mlx->mlx), 1);
	map->img.img = mlx_new_image(mlx->mlx, data->win_w, data->win_h);
	map->img.data = (int *)mlx_get_data_addr(map->img.img, & map->img.bpp, & map->img.size_l, & map->img.endian);
	if (!map->img.img)
		return (1);

	return (0);
}
