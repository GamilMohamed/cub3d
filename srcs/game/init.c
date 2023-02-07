/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:01:09 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/07 03:05:10 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initmlx(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{
	int	z;

	z = 0;
	mlx->mlx = mlx_init(1920 / 2, 1080 / 2, "cub3D", false);
	if (!mlx->mlx)
		return (1);
	data->win_h = 1080 / 2;
	data->win_w = 1920 / 2;
	// mlx_get_screen_size(mlx->mlx, &data->win_w, &data->win_h);
	// mlx->win = mlx_new_window(mlx->mlx, data->win_w, data->win_h, "cub3D");
	// if (!mlx->win)
		// return (ft_free((void **)&mlx->mlx), 1);
	temp->img = mlx_new_image(mlx->mlx, data->win_w, data->win_h);
	if (!temp->img)
		return (1);
	return (0);
}
