/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:30:42 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/13 08:16:09 by mgamil           ###   ########.fr       */
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

// void	map_to_minimap(t_map *map, t_data *data, t_temp *temp, int size)
// {
// 	t_luno2f	map_pos;
// 	t_luno2f	pixel_pos;
// 	int		color;

// 	for (int i = 0; i < (map->maxlen * map->height); i++)
// 	{
// 		map_pos.y = i / map->maxlen;
// 		map_pos.x = i % map->maxlen;
// 		for (int j = 0; j < (size * size); j++)
// 		{
// 			pixel_pos.y = j / size;
// 			pixel_pos.x = j % size;
// 			if (map->map[(int)map_pos.y][(int)map_pos.x] == ' ')
// 				color = create_trgb(map->ceiling);
// 			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '0')
// 				color = create_rgb(0, 0, 0, 0);
// 			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '1')
// 				color = create_rgb(0, 255, 255, 255);
// 			pixel(temp, pixel_pos, color);
// 		}
// 	}
// }

void	map_to_minimap(t_map *map, t_data *data, t_temp *temp, int size)
{
	t_luno2f	map_pos;
	t_luno2f	pixel_pos;
	int		color;
	static int h;


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
				color = create_trgb(map->ceiling);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '0')
				color = create_rgb(0, 207, 185, 151);
			else if (map->map[(int)map_pos.y][(int)map_pos.x] == '1')
				color = create_rgb(0, 155, 161, 123);
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

// void	init_minimap(t_map *map, t_mlx *mlx, t_data *data)
// {
// 	t_temp *temp;

// 	temp = map->mini;
// 	temp->size = 35;
// 	// tempyons = temp->width;
// 	temp->width = map->maxlen * temp->size;
// 	temp->height = map->height * temp->size;
// 	temp->img = mlx_new_image(mlx->mlx, temp->width, temp->height);
// 	temp->addr = mlx_get_data_addr(temp->img, &temp->a, &temp->b, &temp->c);
// }

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

static
t_luno2f	draw_line(t_temp *temp, t_luno2f end, t_luno2f coords)
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
			my_mlx_pixel_put(temp, x, y, 0xFF0000);
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
			my_mlx_pixel_put(temp, x, y, 0xFF0000);
		}
	}
	return ((t_luno2f){x, y});
}

// void	draw_triangle(void *mlx, void *win, int x1, int y1, int x2, int l.y)
// {
// 	int		dx;
// 	int		dy;
// 	int		mid_x;
// 	int		mid_y;

// 	dx = x2 - x1;
// 	dy = y2 - y1;
// 	mid_x = (x1 + x2) / 2;
// 	mid_y = (y1 + y2) / 2;
// 	mlx_pixel_put(mlx, win, x1, y1, 0xFFFFFF);
// 	mlx_pixel_put(mlx, win, x2, y2, 0xFFFFFF);
// 	mlx_pixel_put(mlx, win, mid_x - dy, mid_y + dx, 0xFFFFFF);
// 	mlx_pixel_put(mlx, win, mid_x + dy, mid_y - dx, 0xFFFFFF);
// }


void	draw_triangle_big(t_temp *temp, t_luno2f m, t_luno2f l, t_luno2f r)
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	d;

	dx = l.x - m.x;
	dy = l.y - m.y;
	d = 2 * dy - dx;
	y = m.y;
	x = m.x;
	while (x <= l.x)
	{
		my_mlx_pixel_put(temp, x, y, 0xFF0000);
		if (d > 0)
		{
			y++;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x++;
	}
	dx = r.x - l.x;
	dy = r.y - l.y;
	d = 2 * dy - dx;
	y = l.y;
	x = l.x;
	while (x <= r.x)
	{
		my_mlx_pixel_put(temp, x, y, 0xFF0000);
		if (d > 0)
		{
			y++;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x++;
	}
	dx = r.x - m.x;
	dy = r.y - m.y;
	d = 2 * dy - dx;
	y = m.y;
	x = m.x;
	while (x <= r.x)
	{
		my_mlx_pixel_put(temp, x, y, 0xFF0000);
		if (d > 0)
		{
			y++;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x++;
	}
}

t_luno2f	draw_triangle(t_temp *temp, t_luno2f ray, t_luno2f coords)
{
	t_luno2f d;
	t_luno2f mid;

	d.x = coords.x - ray.x;
	d.y = coords.y - ray.y;
	mid.x = (ray.x + coords.x) / 2;
	mid.y = (ray.y + coords.y) / 2;
	my_mlx_pixel_put(temp, ray.x, ray.y, 0x00FF00);
	// my_mlx_pixel_put(temp, coords.x, coords.y, 0x00FF00);
	my_mlx_pixel_put(temp, mid.x - d.y, mid.y + d.x, 0x00FF00);
	my_mlx_pixel_put(temp, mid.x + d.y, mid.y - d.x, 0x00FF00);
	return (mid);
}

void fill_triangle(t_temp *temp, int x1, int y1, int x2, int y2, int x3, int y3)
{
    int x_min = x1;
    int x_max = x1;
    int y_min = y1;
    int y_max = y1;

    if (x2 < x_min)
        x_min = x2;
    else if (x2 > x_max)
        x_max = x2;
    if (y2 < y_min)
        y_min = y2;
    else if (y2 > y_max)
        y_max = y2;
    if (x3 < x_min)
        x_min = x3;
    else if (x3 > x_max)
        x_max = x3;
    if (y3 < y_min)
        y_min = y3;
    else if (y3 > y_max)
        y_max = y3;

    for (int x = x_min; x <= x_max; x++)
    {
        for (int y = y_min; y <= y_max; y++)
        {
            int a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
            int b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
            int c = 1 - a - b;
            if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1)
                my_mlx_pixel_put(temp, x, y, 0xFF0000);
        }
    }
}

void draw_triangle_3(t_temp *temp, int x1, int y1, int x2, int y2, int x3, int y3)
{
    int dx1 = x2 - x1;
    int dy1 = y2 - y1;
    int dx2 = x3 - x2;
    int dy2 = y3 - y2;
    int dx3 = x1 - x3;
    int dy3 = y1 - y3;

    if (dx1 * dy2 > dy1 * dx2)
    {
        for (int x = x1; x <= x2; x++)
        {
            int y = y1 + (x - x1) * dy1 / dx1;
            int y2 = y3 + (x - x3) * dy3 / dx3;
            int y_min = (y < y2) ? y : y2;
            int y_max = (y > y2) ? y : y2;
            for (int yi = y_min; yi <= y_max; yi++)
                my_mlx_pixel_put(temp, x, yi, 0xFF0000);
        }
    }
    else
    {
        for (int x = x2; x <= x3; x++)
        {
            int y = y2 + (x - x2) * dy2 / dx2;
            int y1 = y1 + (x - x1) * dy1 / dx1;
            int y_min = (y < y1) ? y : y1;
            int y_max = (y > y1) ? y : y1;
            for (int yi = y_min; yi <= y_max; yi++)
                my_mlx_pixel_put(temp, x, yi, 0xFF0000);
        }
    }
}

void	draw_one_ray(t_temp *temp, t_luno2f coords, t_luno2f dir)
{
	t_luno2f middle;
	t_luno2f d;
	t_luno2f left;
	t_luno2f mid;
	t_luno2f right;

	middle.x = coords.x + dir.y * 4;
	middle.y = coords.y + dir.x * 4;

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
	fill_triangle(temp, left.x, left.y, right.x, right.y, middle.x, middle.y);

void	fill_minimap(t_map *map, t_mlx *mlx, t_data *data)
{
	(void)mlx;
	int size = map->mini->size;
	map_to_minimap(map, data, map->mini, size);
	docircle(map->mini, map->mini->coords, 3);
	draw_one_ray(map->mini, map->mini->coords, map->plane->dir);
}

