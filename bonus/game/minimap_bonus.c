/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/18 03:20:54 by mgamil           ###   ########.fr       */
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

void	map_to_minimap(t_map *map, t_temp *temp, int size)
{
	t_luno2i	map_pos;
	t_luno2i	pixel_pos;
	int			color;

	for (int i = 0; i < (map->maxlen * map->height); i++)
	{
		map_pos.x = i % map->maxlen; // 0 -> 200
		map_pos.y = i / map->maxlen; // 0 -> 150
		for (int j = 0; j < (size * size); j++)
		{
			pixel_pos.y = j / size;
			pixel_pos.x = fmod(j, size);
			color = get_color_for_map_char(map->map[map_pos.y][map_pos.x]);
			if (color != 0)
			{
				t_luno2i plz;
				plz.y = (pixel_pos.y + map_pos.y * (int)size);
				plz.x = (pixel_pos.x + map_pos.x * (int)size);
				if (plz.x >= WIDTH || plz.y >= HEIGHT)
					continue;
				map->plane->buff[(plz.y)][(plz.x)] = color;
			}
		}
	}
	temp->coords.x = (map->plane->pos.y * size);
	temp->coords.y = (map->plane->pos.x * size);
}

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
	mid.x = (middle.x + coords.x) / 2;
	mid.y = (middle.y + coords.y) / 2;
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
	if (map->mini->coords.x >= WIDTH || map->mini->coords.y >= HEIGHT)
		return;
	docircle(map, map->mini->coords, 3);	
	draw_one_ray_xx(map->mini, map->mini->coords, map->plane->dir, map);
}
