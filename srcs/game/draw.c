/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:03:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/08 01:36:31 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		condition(int x, int y, int size, t_map *map)
{
	if (y/24 > 0 && y/24 < map->height && x/24 > 0 && x/24 < map->maxlen && map->map[y/24][x/24] == '1')
		return (1);
	if ((x % 24 == 23) && (y % 24 == 0))
	{
		if (map->map[(y - 1)/24][x/24] == '1' && map->map[y/24][(x + 1)/24] == '1')
			return (1);
	}
	else if ((x % 24 == 0) && (y % 24 == 0))
	{
		if (map->map[(y - 1)/24][x/24] == '1' && map->map[y/24][(x - 1)/24] == '1')
			return (1);
	}
	else if ((x % 24 == 23) && (y % 24 == 23))
	{
		if (map->map[(y + 1)/24][x/24] == '1' && map->map[y/24][(x + 1)/24] == '1')
			return (1);
	}
	else if ((x % 24 == 0) && (y % 24 == 23))
	{
		if (map->map[(y + 1)/24][x/24] == '1' && map->map[y/24][(x - 1)/24] == '1')
			return (1);
	}
	return (0);
}


void	draw_circle(t_temp *tmp, Luno2f coords, int r)
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

Luno2f	draw_line_rays(t_map *map, Luno2f end, Luno2f coords, bool print)
{
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

	dx = end.x - coords.x;
	dy = end.y - coords.y;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	incx = 1;
	if (end.x < coords.x)
		incx = -1;
	incy = 1;
	if (end.y < coords.y)
		incy = -1;
	x = (int)coords.x;
	y = (int)coords.y;
	if (dx > dy)
	{
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			if (!condition(x, y, 24, map))
				my_mlx_pixel_put(map->mini, x, y, create_trgb((int [3]){255, 255, 255}));
			else
				return ((Luno2f){x, y});
		}
	}
	else
	{
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (e >= 0)
			{
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			if (!condition(x, y, 24, map))
				my_mlx_pixel_put(map->mini, x, y, create_trgb((int [3]){255, 255, 255}));
			else
				return ((Luno2f){x, y});
		}
	}
	return ((Luno2f){x, y});
}

void	my_mlx_pixel_put(t_temp *temp, int x, int y, int color)
{
	char	*dst;

	dst = temp->addr + (y * temp->b + x * (temp->a / 8));
	*(unsigned int*)dst = color;
}

Luno2f	docircle(t_temp *temp, Luno2f coords, int ray)
{
	double r, s, x, y;
	Luno2f circle;

	r = coords.x;
	s = coords.y;
	for (circle.x = (r - ray); circle.x < (r + ray); circle.x++)
	{
		for (circle.y = (s - ray); circle.y < (s + ray); circle.y++)
		{
			if (pow(circle.x - r, 2) + pow(circle.y - s, 2) <= pow(ray, 2))
				my_mlx_pixel_put(temp, circle.x, circle.y, create_rgb(0, 250, 214, 165));
		}
	}
	return (circle);
}

void	pixel(t_temp *temp, Luno2f coords, int color)
{
	my_mlx_pixel_put(temp, coords.x, coords.y, color);
}