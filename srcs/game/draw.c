/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:03:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/07 02:40:23 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		condition(int x, int y, int size, char **map)
{
	// if (!(x % 35) || !(y % 35))
	// {
		if ((x % 35 == 34) && (y % 35 == 0))
		{
			if (map[(y - 1)/35][x/35] == '1' && map[y/35][(x + 1)/35] == '1')
				return (1);
		}
		else if ((x % 35 == 0) && (y % 35 == 0))
		{
			if (map[(y - 1)/35][x/35] == '1' && map[y/35][(x - 1)/35] == '1')
				return (1);
		}
		else if ((x % 35 == 34) && (y % 35 == 34))
		{
			if (map[(y + 1)/35][x/35] == '1' && map[y/35][(x + 1)/35] == '1')
				return (1);
		}
		else if ((x % 35 == 0) && (y % 35 == 34))
		{
			if (map[(y + 1)/35][x/35] == '1' && map[y/35][(x - 1)/35] == '1')
				return (1);
		}
	// }
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

	double r = 0;
	int colorize = 0;

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
			if (print == 1)
				my_mlx_pixel_put(map->mini, x, y, create_trgb((int [3]){255 - (int)r / 2, 255 - (int)r / 2, 255}));
			if (print && y/35 > 0 && y/35 < map->height && x/35 > 0 && x/35 < map->maxlen && map->map[y/35][x/35] != '1' && !condition(x, y, 35, map->map))
				;// my_mlx_pixel_put(map->mini, x, y, create_trgb((int [3]){255 - (int)r / 2, 255 - (int)r / 2, 255}));
			else
				return ((Luno2f){x, y});
			if (r < 255)
				r += 1;
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
			if (print == 1)
				my_mlx_pixel_put(map->mini, x, y, create_trgb((int [3]){255 - (int)r / 2, 255 - (int)r / 2, 255}));
			if (print && y/35 > 0 && y/35 < map->height && x/35 > 0 && x/35 < map->maxlen && map->map[y/35][x/35] != '1' && !condition(x, y, 35, map->map))
				; // my_mlx_pixel_put(map->mini, x, y, create_trgb((int [3]){255 - (int)r / 2, 255 - (int)r / 2, 255}));
			else
				return ((Luno2f){x, y});
			if (r < 255)
				r += 1;
		}
	}
	return ((Luno2f){x, y});
}

void	my_mlx_pixel_put(t_temp *temp, int x, int y, int color)
{
	// char	*dst;

	mlx_put_pixel(temp->img, x, y, color);
	// dst = temp->addr + (y * temp->b + x * (temp->a / 8));
	// *(unsigned int *)dst = color;
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