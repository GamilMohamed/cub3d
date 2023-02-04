/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/04 09:22:56 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printcoords(Luno2i val, Luno2f val2)
{
	if (val.x)
		printf("val.x:%i, val.y:%i\n", val.x, val.y);
	if (val2.x)
		printf("val2.x:%f, val2.y:%f\n", val2.x, val2.y);
}

void	my_mlx_pixel_put(t_temp *temp, int x, int y, int color)
{
	char	*dst;

	dst = temp->addr + (y * temp->b + x * (temp->a / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(int t, int a, int b, int c)
{
	return (t << 24 | a << 16 | b << 8 | c);
}

int	create_trgb(int tab[3])
{
	return (0 << 24 | tab[0] << 16 | tab[1] << 8 | tab[2]);
}

void	destroywindows(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

void	backgroundcolor(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{
	int	i;
	int	j;
	int	ceiling;
	int	floor;

	i = -1;
	ceiling = create_trgb(map->ceiling);
	floor = create_trgb(map->floor);
	while (++i < data->win_w)
	{
		j = -1;
		while (++j < data->win_h)
		{
			if (j < data->win_h / 2 && j < data->win_w / 2)
				my_mlx_pixel_put(temp, i, j, ceiling);
			else
				my_mlx_pixel_put(temp, i, j, floor);
		}
	}
}

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

void	my_color_pixel_put(t_temp *temp, Luno2f coords, int color)
{
	my_mlx_pixel_put(temp, coords.x, coords.y, color);
}

void	draw_line(t_temp *temp, Luno2f coords, Luno2f end, int color)
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
	x = coords.x;
	y = coords.y;
	if (dx > dy)
	{
		my_mlx_pixel_put(temp, x, y, color);
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
			my_mlx_pixel_put(temp, x, y, color);
		}
	}
	else
	{
		my_mlx_pixel_put(temp, x, y, color);
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
			my_mlx_pixel_put(temp, x, y, color);
		}
	}
}

void	draw_circle(t_temp *tmp, int xc, int yc, int r)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;

	while (y >= x)
	{
		my_mlx_pixel_put(tmp, xc + x, yc + y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, xc + y, yc + x, 0xFFFFFF);
		my_mlx_pixel_put(tmp, xc - x, yc + y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, xc - y, yc + x, 0xFFFFFF);
		my_mlx_pixel_put(tmp, xc + x, yc - y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, xc + y, yc - x, 0xFFFFFF);
		my_mlx_pixel_put(tmp, xc - x, yc - y, 0xFFFFFF);
		my_mlx_pixel_put(tmp, xc - y, yc - x, 0xFFFFFF);
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

void	rotate_line(t_temp *tmp, Luno2f coords, int r, double angle)
{
	Luno2f end;
	double rad;

	// draw_circle(tmp, coords.x, coords.y, r / 2);
	docircle(tmp, coords, r / 2);
	rad = angle * M_PI / 180;
	end.x = coords.x + r * 2 * cos(rad);
	end.y = coords.y + r * 2 * sin(rad);
	draw_line(tmp, coords, end, create_rgb(0, 147, 151, 12));	
}


void	fillminimap(t_map *map, t_data *data, t_temp *temp, int size)
{
	int		h;
	Luno2f	coords;
	Luno2f	map_pos;
	Luno2f	pixel_pos;
	int		color;

	h = 0;
	color = 0;
	for (map_pos.x = 0; map_pos.x < map->maxlen; map_pos.x++)
	{
		for (map_pos.y = 0; map_pos.y < map->height; map_pos.y++)
		{
			for (pixel_pos.y = 0; pixel_pos.y < size; pixel_pos.y++)
			{
				for (pixel_pos.x = 0; pixel_pos.x < size; pixel_pos.x++)
				{
					if (map->map[(int)map_pos.y][(int)map_pos.x] == ' ')
						color = create_rgb(0, 97, 118, 75);
					else if (map->map[(int)map_pos.y][(int)map_pos.x] == '0') // || map->map[(int)map_pos.y][(int)map_pos.x] == 'N')
						color = create_rgb(0, 207, 185, 151);
					else if (map->map[(int)map_pos.y][(int)map_pos.x] == '1')
						color = create_rgb(0, 155, 161, 123);
					if (map->map[(int)map_pos.y][(int)map_pos.x] == 'N' && !h)
					{
						color = create_rgb(0, 207, 185, 255);
						if (!h++)
							coords = pixel_pos + (data->player_pos * size + size / 2);
					}
					my_color_pixel_put(temp, (pixel_pos + map_pos * size),
							color);
				}
			}
		}
	}
	rotate_line(temp, coords, size/2, data->rotation);
}

t_temp	ft_printtomlx(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp	mini;
	int		size;

	size = 70;
	mini.width = map->maxlen * size;
	mini.height = map->height * size;
	mini.img = mlx_new_image(mlx->mlx, mini.width, mini.height);
	mini.addr = mlx_get_data_addr(mini.img, &mini.a, &mini.b, &mini.c);
	fillminimap(map, data, &mini, size);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mini.img, 20, 20);
	return (mini);
}

void	movetodirection(t_map *map, double y, double x)
{
	Luno2i	enint;
	Luno2i	p;

	double px, py;
	int enintx, eninty;
	py = map->data->player_pos.y;
	px = map->data->player_pos.x;
	py += ((map->data->player_pos.y / (int)map->data->player_pos.y) > 0.5)
		- 0.5;
	px += ((map->data->player_pos.x / (int)map->data->player_pos.x) > 0.5)
		- 0.5;
	if (map->map[(int)py + (int)y][(int)px + (int)x] != '1')
	{
		map->map[(int)py][(int)px] = '0';
		map->data->player_pos.x += x / 4;
		map->data->player_pos.y += y / 4;
		enintx = map->data->player_pos.x + ((map->data->player_pos.x
					/ (int)map->data->player_pos.x) > 0.5) - 0.5;
		eninty = map->data->player_pos.y + ((map->data->player_pos.y
					/ (int)map->data->player_pos.y) > 0.5) - 0.5;
		map->map[eninty][enintx] = map->data->player;
	}
}

int	move(int key, t_map *map)
{
	if (key == ESCAPE)
		return (mlx_loop_end(map->mlx->mlx));
	if (key == W)
		movetodirection(map, -1, 0);
	if (key == S)
		movetodirection(map, 1, 0);
	if (key == D)
		movetodirection(map, 0, 1);
	if (key == A)
		movetodirection(map, 0, -1);
	if (key == LEFT)
		map->data->rotation -= 15;
	if (key == RIGHT)
		map->data->rotation += 15;
	ft_printtomlx(map, map->mlx, map->data);
	return (0);
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp	temp;

	int r;

	// t_temp
	r = 0;
	if (initmlx(map, mlx, data, &temp))
		return (1);
	data->rotation = 0;
	mlx_put_image_to_window(mlx->mlx, mlx->win, temp.img, 0, 0);
	ft_printtomlx(map, mlx, data);
	mlx_key_hook(mlx->win, &move, map);
	mlx_hook(mlx->win, r, KeyPressMask, &move, data);
	mlx_loop(mlx->mlx);
	mlx_destroy_image(mlx->mlx, temp.img);
	// mlx_destroy_image(mlx->mlx, mini.img);
	destroywindows(mlx);
	return (0);
}

/*

ETAPE 1: mini so long

ETAPE 2: tourner camera

ETAPE 3: ligne de 10pixel bien droit 

ETAPE 4: la ligne doit mtn sarreter au 1er mur

ETAPE 5: ligne x fov




*/