/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/17 12:32:54 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_color_for_map_char(char c)
{
	if (c == '1')
		return (0x9BA17B);
	else if (c == '0')
		return (0xCFB997);
	else if (c == 'D')
		return (0x9B0B00);
	else if (c == 'C')
		return (0x0B9737);
	return (0);
}

void print_minimap(t_map *map, char **grid, int map_width, int map_height, int player_x, int player_y, void *mlx_ptr, int minimap_size)
{
	for (int y = (25); y < (175); y++)
	{
		for (int x = (25); x < (175); x++)
		{
			if (pow(x - 100, 2) + pow(y - 100, 2) <= pow(75, 2))
			{
				// double distance = sqrt(pow(x - 100, 2) + pow(y - 100, 2));
				int cell_x = player_x + (x - 100);
				int cell_y = player_y + (y - 100);
				if (cell_x < 0 || cell_x >= map_width || cell_y < 0 || cell_y >= map_height)
					continue;
				// int dx = cell_x - player_x;
				// int dy = cell_y - player_y;
				char c = grid[cell_y][cell_x];
				int color = get_color_for_map_char(c);
				if (cell_y == map->pos_q.x && cell_x == map->pos_q.y)
					color = 0x0FFF0;
				if (color)
				{
					for (int v = 0; v < 5; v++)
					{
						for (int u = 0; u < 5; u++)
							map->plane->buff[y + v * 5][x + u * 5] = color;
					}
					
				}
			}
		}
	}
	docircle(map, (t_luno2f){100, 100}, 3);
}

void	map_to_minimap(t_map *map, t_temp *temp, int size)
{
	t_luno2i	map_pos;
	t_luno2i	pixel_pos;
	int			color;

	print_minimap(map, map->map, map->maxlen, map->height, map->plane->pos.y, map->plane->pos.x, map->mlx->mlx, 200);

	// for (int i = 0; i < (map->maxlen * map->height); i++)
	// {
	// 	map_pos.x = i % map->maxlen;
	// 	map_pos.y = i / map->maxlen;
	// 	for (int j = 0; j < (size * size); j++)
	// 	{
	// 		pixel_pos.y = j / size;
	// 		pixel_pos.x = j % size;
	// 		color = get_color_for_map_char(map->map[map_pos.y][map_pos.x]);
	// 		if (color != 0)
	// 			map->plane->buff[(pixel_pos.y + map_pos.y * size)][(pixel_pos.x
	// 					+ map_pos.x * size)] = color;
	// 	}
	// }
	// temp->coords.x = (map->plane->pos.y * size);
	// temp->coords.y = (map->plane->pos.x * size);
}

	// void map_to_minimap(t_map *map, t_temp *temp, int size)
	// {
	// 	t_luno2f player;

	// 	print_minimap(map, map->map, map->maxlen, map->height, map->plane->pos.y, map->plane->pos.x, map->mlx->mlx, 200);
	// }

t_luno2f	docircle(t_map *map, t_luno2f coords, int ray)
{
	t_luno2f	circle;

	double r, s;
	r = coords.x;
	s = coords.y;
	for (circle.x = (r - ray); circle.x < (r + ray); circle.x++)
	{
		for (circle.y = (s - ray); circle.y < (s + ray); circle.y++)
		{
			if (pow(circle.x - r, 2) + pow(circle.y - s, 2) <= pow(ray, 2))
				map->plane->buff[(int)circle.y][(int)circle.x] = 16777215;
		}
	}
	return (circle);
}

void	draw_one_ray_xx(t_temp *temp, t_luno2f coords, t_luno2f dir, t_map *map)
{
	t_luno2f	middle;
	t_luno2f	d;
	t_luno2f	left;
	t_luno2f	mid;
	t_luno2f	right;

	middle.x = coords.x + dir.y * 5;
	middle.y = coords.y + dir.x * 5;
	d.x = coords.x - middle.x;
	d.y = coords.y - middle.y;
	mid = (middle + coords) / 2;
	left.x = mid.x - d.y;
	left.y = mid.y + d.x;
	right.x = mid.x + d.y;
	right.y = mid.y - d.x;
	map->plane->buff[(int)middle.y][(int)middle.x] = 0x0000FF;
	temp->front = middle;
}

void	fill_minimap(t_map *map, t_mlx *mlx)
{
	int	size;

	(void)mlx;
	size = map->mini->size;
	map_to_minimap(map, map->mini, size);
	// docircle(map, map->mini->coords, 3);
	draw_one_ray_xx(map->mini, (t_luno2f){100, 100}, map->plane->dir, map);
}
