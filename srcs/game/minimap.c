/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:04:40 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/07 03:15:50 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_to_minimap(t_map *map, t_data *data, t_temp *temp, int size)
{
	int		h;
	Luno2f	coords;
	Luno2f	map_pos;
	Luno2f	pixel_pos;
	int		color;

	h = 0;
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
				color = 0;
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '0') // || map->map[(int)map_pos.y][(int)map_pos.x] == 'N')
				color = create_rgb(0, 207, 185, 151);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '1')
				color = create_rgb(0, 155, 161, 123);
			if (ft_strchr("NSEW", map->map[(int)map_pos.y][(int)map_pos.x]) && !h)
			{
				color = create_rgb(0, 207, 185, 255);
				if (!h++)
					temp->coords = pixel_pos + (data->player_pos * size + size / 2);
			}
			pixel(temp, (pixel_pos + map_pos * size), 1);
		}
	}
}


void	init_minimap(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp *temp;

	temp = map->mini;
	temp->size = 35;
	// tempyons = temp->width;
	temp->width = map->maxlen * temp->size;
	temp->height = map->height * temp->size;
	temp->img = mlx_new_image(mlx->mlx, temp->width, temp->height);
	// temp->addr = mlx_get_data_addr(temp->img, &temp->a, &temp->b, &temp->c);
}

void	fill_minimap(t_map *map, t_mlx *mlx, t_data *data)
{
	map_to_minimap(map, data, map->mini, map->mini->size);
	camera_rays(map->mini, map, map->mini->coords, map->mini->size / 2);

	for (size_t i = 0; i < data->win_w; i++)
	{
		// camera_plane(map, map->plane, i);
		/* code */
	}
	
// void	camera_plane(t_map *map, t_plane *p, int x)

}
