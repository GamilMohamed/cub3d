/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:04:40 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/08 03:16:31 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_to_minimap(t_map *map, t_data *data, t_temp *temp, int size)
{
	int		h;
	Luno2f	map_pos;
	Luno2f	pixel_pos;
	int		color;

	color = 0;
	for (int i = 0; i < (map->maxlen * map->height); i++)
	{
		map_pos.y = i / map->maxlen;
		map_pos.x = i % map->maxlen;
		for (int j = 0; j < (size * size); j++)
		{
			pixel_pos.y = j / size;
			pixel_pos.x = j % size;
			if (map->map[(int)map_pos.y][(int)map_pos.x] == ' ')
				color = create_rgb(1, 25, 25, 25);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '0') // || map->map[(int)map_pos.y][(int)map_pos.x] == 'N')
				color = create_rgb(0, 207, 185, 151);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '1')
				color = create_rgb(0, 155, 161, 123);
			pixel(temp, (pixel_pos + map_pos * size), color);
		}
	}
}

void	init_minimap(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp *temp;

	// tempyons = temp->width;
	temp = map->mini;
	temp->size = 24;
	temp->width = (data->win_w / 64 * temp->size);
	temp->height = (data->win_h / 64 * temp->size);
	temp->img = mlx_new_image(mlx->mlx, temp->width, temp->height);
	temp->addr = mlx_get_data_addr(temp->img, &temp->a, &temp->b, &temp->c);
}
