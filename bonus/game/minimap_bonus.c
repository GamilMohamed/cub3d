/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/15 19:05:46 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_temp *temp, int x, int y, int color)
{
	char	*dst;

	dst = temp->addr + (y * temp->b + x * (temp->a / 8));
	*(unsigned int *)dst = color;
}

void	pixel(t_temp *temp, t_luno2f coords, int color)
{
	my_mlx_pixel_put(temp, coords.x, coords.y, color);
}

void	map_to_minimap(t_map *map, t_data *data, t_temp *temp, int size)
{
	t_luno2f	map_pos;
	t_luno2f	pixel_pos;
	int		color;
	static int h;
	static int r;


	color = 0;
	for (int i = 0; i < (map->maxlen * map->height); i++)
	{
		map_pos.y = i / map->maxlen;
		map_pos.x = i % map->maxlen;
		for (int j = 0; j < (size * size); j++)
		{
			pixel_pos.y = j / size;
			pixel_pos.x = j % size;
			if (map->map[(int)map_pos.y][(int)map_pos.x] == ' ' && !r)
				color = create_trgb(map->ceiling);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '0')
				color = create_rgb(0, 207, 185, 151);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '1')
				color = create_rgb(0, 155, 161, 123);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == 'D')
				color = create_rgb(0, 155, 11, 0);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == 'C')
				color = create_rgb(0, 11, 151, 55);
			if (ft_strchr("NSEW", map->map[(int)map_pos.y][(int)map_pos.x]) && !h)
			{
				map->map[(int)map_pos.y][(int)map_pos.x] = '0';
				color = create_rgb(0, 207, 185, 255);
				// temp->coords = pixel_pos + (map->plane->pos * size + size / 2);
				// printf("coor %f %f\n", temp->coords.x, temp->coords.y);
				h++;
			}
			pixel(temp, (pixel_pos + map_pos * size), color);
			// printf("posi %f %f\n", pixel_pos.x, pixel_pos.y);
		}
	}
	// r = 1;
	// printf("map %d %d\n", map->plane->map.x, map->plane->map.y);
	// printf("pos %f %f\n", map->plane->pos.x, map->plane->pos.y);
	temp->coords.x = (map->plane->pos.y * size );
	temp->coords.y = (map->plane->pos.x * size );
	// pixel(temp, temp->coords + 5, create_rgb(0, 255, 0, 0));
	// pixel(temp, temp->coords, create_rgb(0, 255, 0, 0));
	// pixel(temp, temp->coords - 5, create_rgb(0, 255, 0, 0));
}


void	draw_circle(t_temp *tmp, t_luno2f coords, int r)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;

	while (y >= x)
	{
		my_mlx_pixel_put(tmp, coords.x + x, coords.y + y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, coords.x + y, coords.y + x, 0xFFFFFF);
		my_mlx_pixel_put(tmp, coords.x - x, coords.y + y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, coords.x - y, coords.y + x, 0xFFFFFF);
		my_mlx_pixel_put(tmp, coords.x + x, coords.y - y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, coords.x + y, coords.y - x, 0xFFFFFF);
		my_mlx_pixel_put(tmp, coords.x - x, coords.y - y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, coords.x - y, coords.y - x, 0xFFFFFF);
		if (d < 0)
			d = d + 4 * x + 6;
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

t_luno2f	docircle(t_temp *temp, t_luno2f coords, int ray)
{
	double r, s, x, y;
	t_luno2f circle;

	r = coords.x;
	s = coords.y;
	for (circle.x = (r - ray); circle.x < (r + ray); circle.x++)
	{
		for (circle.y = (s - ray); circle.y < (s + ray); circle.y++)
		{
			if (pow(circle.x - r, 2) + pow(circle.y - s, 2) <= pow(ray, 2))
				my_mlx_pixel_put(temp, circle.x, circle.y, create_rgb(0, 255, 255, 255));
		}
	}
	return (circle);
}

void	draw_one_ray(t_temp *temp, t_luno2f coords, t_luno2f dir)
{
	t_luno2f middle;
	t_luno2f d;
	t_luno2f left;
	t_luno2f mid;
	t_luno2f right;

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
	pixel(temp, left, 0xFF0000);
	pixel(temp, middle, 0x00FF00);
	pixel(temp, right, 0x0000FF);
	temp->front = middle;
	// fill_triangle(temp, left.x, left.y, right.x, right.y, middle.x, middle.y);
}

void	fill_minimap(t_map *map, t_mlx *mlx, t_data *data)
{
	(void)mlx;
	int size = map->mini->size;
	map_to_minimap(map, data, map->mini, size);
	docircle(map->mini, map->mini->coords, 3);
	draw_one_ray(map->mini, map->mini->coords, map->plane->dir);
}

