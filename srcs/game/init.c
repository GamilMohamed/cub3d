/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:01:09 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/06 08:05:30 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initmlx(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{
	int	z;

	z = 0;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx_get_screen_size(mlx->mlx, &data->win_w, &data->win_h);
	mlx->win = mlx_new_window(mlx->mlx, data->win_w, data->win_h, "cub3D");
	if (!mlx->win)
		return (ft_free((void **)&mlx->mlx), 1);
	temp->img = mlx_new_image(mlx->mlx, data->win_w, data->win_h);
	if (!temp->img)
		return (destroywindows(mlx), 1);
	temp->addr = mlx_get_data_addr(temp->img, &temp->a, &temp->b, &temp->c);
	backgroundcolor(map, mlx, data, temp);
	return (0);
}
