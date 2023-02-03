/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/03 06:35:45 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_printf("data->win_w:%i, data->win_h:%i\n", data->win_w, data->win_h);
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


void	docircle(t_temp *temp, Luno2f coords, int ray)
{
	double r, s, x, y;
	r = coords.x;
	s = coords.y;

	printf("POSITION X:%f, POSITION Y:%f size:%i\n", r, s, ray);
	for (x = (r - ray); x < (r + ray); x++)
	{
		for (y = (s - ray); y < (s + ray); y++)
		{
			if (pow(x - r, 2) + pow(y - s, 2) <= pow(ray, 2))
				my_mlx_pixel_put(temp, x, y, create_rgb(0, 250, 214, 165));
			// else
			// 	my_mlx_pixel_put(temp, x, y, create_rgb(255, 207, 185, 255));
		}
	}
	printf("fin du cercle x:%f, y:%f size:%i\n", x, y, ray);
}



// void	fillminimap(t_map *map, t_data *data, t_temp *temp, int size)
// {
// 	int h = 0;
// 	Luno2f coords;
// 	Luno2f guette;
// 	Luno2f map_pos;
// 	Luno2f pixel_pos;

// 	int color = 0;
// 	for (size_t z = 0; z < map->maxlen; z++)
// 	{
// 		for (size_t y = 0; y < map->height; y++)
// 		{
// 			for (size_t v = 0; v < size; v++)
// 			{
// 				for (size_t x = 0; x < size; x++)
// 				{
// 					if (map->map[y][z] == ' ')
// 						color = create_rgb(0, 97, 118, 75);
// 					else if (map->map[y][z] == '0') //|| map->map[y][z] == 'N')
// 						color = create_rgb(0, 207, 185, 151);
// 					else if (map->map[y][z] == '1')
// 						color = create_rgb(0, 155, 161, 123);
// 					if (map->map[y][z] == 'N' && !h)
// 					{
// 						color = create_rgb(0, 255, 25, 0);
// 						if (!h++)
// 						{
// 							coords.xy = (Luno2f){x, v};
// 							guette = coords + (data->player_pos * size + size / 2);
// 						}
// 					}
// 					my_mlx_pixel_put(temp, x + z * size, v + y * size, color);
// 				}
// 			}
// 		}
// 	}
// 	docircle(temp, guette, size / 2);
// 		// 	j++;
// 		// }
// 		// i++;
// 	// }*
// }

void	my_color_pixel_put(t_temp *temp, Luno2f coords, int color)
{
	my_mlx_pixel_put(temp, coords.x, coords.y, color);
}

void	fillminimap(t_map *map, t_data *data, t_temp *temp, int size)
{
	int h = 0;
	Luno2f coords;
	Luno2f map_pos;
	Luno2f pixel_pos;

	int color = 0;
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
					else if (map->map[(int)map_pos.y][(int)map_pos.x] == '0' || map->map[(int)map_pos.y][(int)map_pos.x] == 'N')
						color = create_rgb(0, 207, 185, 151);
					else if (map->map[(int)map_pos.y][(int)map_pos.x] == '1')
						color = create_rgb(0, 155, 161, 123);
					if (map->map[(int)map_pos.y][(int)map_pos.x] == 'N' && !h)
					{
						color = create_rgb(0, 207, 185, 0);
						if (!h++)
						{
							coords = pixel_pos;
							coords += (data->player_pos * size + size / 2);
							// printf("coords.x:%f, coords.y:%f\n", coords.x, coords.y);
						}
					}
					my_color_pixel_put(temp, (pixel_pos + map_pos * size), color);
					// my_mlx_pixel_put(temp, pixel_pos.x + map_pos.x * size, pixel_pos.y + map_pos.y * size, color);
				}
			}
		}
	}
	docircle(temp, coords, size / 2);
}

void	ft_printtomlx(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp	mini;

	int size;
	size = 40;
	// ft_printf("realmap:%i|%i\n", map->maxlen, map->height);
	// ft_printf("window:%i|%i\n", data->win_w, data->win_h);
	// ft_printf("size=%i\n", size);
	mini.width = map->maxlen * size;
	mini.height = map->height * size;
	// ft_printf("minimap:%i|%i\n", mini.width, mini.height);
	mini.img = mlx_new_image(mlx->mlx, mini.width, mini.height);
	mini.addr = mlx_get_data_addr(mini.img, &mini.a, &mini.b, &mini.c);
	fillminimap(map, data, & mini, size);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mini.img, 0, 0);
	// ft_printmap(map->map, 0);
}


void	movetodirection(t_map *map, double y, double x)
{
	int	px, py;
	int enintx, eninty;
	Luno2i enint;
	Luno2i p;

	py = map->data->player_pos.y;
	px = map->data->player_pos.x;
	printf("BEFORE py:%i, px:%i %f|%f\n", py, px, y, x);
	py += ((map->data->player_pos.y / (int)map->data->player_pos.y) > 0.5) - 0.5;
	px += ((map->data->player_pos.x / (int)map->data->player_pos.x) > 0.5) - 0.5;
	printf("AFTER py:%i, px:%i %f|%f\n", py, px, y, x);
	if (map->map[py + (int)y][px + (int)x] != '1')
	{
		ft_printf("%rdeplacement%0\n");
		// printf("AVANT ft_move :player_pos.y=%f\n", map->data->player_pos.y);
		// printf("AVANT ft_move :player_pos.x=%f\n", map->data->player_pos.x);
		// printf("y*2:%f, x*2:%f\n", y, x);
		map->map[py][px] = '0';
		printf("%f,%f\n", map->data->player_pos.y, map->data->player_pos.x);
		map->data->player_pos.x += x / 4;
		map->data->player_pos.y += y / 4;
		// printf("APRES ft_move :player_pos.y=%f\n", map->data->player_pos.y);
		// printf("APRES ft_move :player_pos.x=%f\n", map->data->player_pos.x);
		enintx = map->data->player_pos.x + ((map->data->player_pos.x / (int)map->data->player_pos.x) > 0.5) - 0.5;
		eninty = map->data->player_pos.y + ((map->data->player_pos.y / (int)map->data->player_pos.y) > 0.5) - 0.5;
		map->map[eninty][enintx] = map->data->player;

	}
}

int	move(int key, t_map *map)
{
	if (key == ESCAPE)
		return (mlx_loop_end(map->mlx->mlx));
	printf("map->data->player_pos.y:%f, map->data->player_pos.x:%f\n", map->data->player_pos.y, map->data->player_pos.x);
	if (key == W)
		movetodirection(map, -1, 0);
	if (key == S)
		movetodirection(map, 1, 0);
	if (key == D)
		movetodirection(map, 0, 1);
	if (key == A)
		movetodirection(map, 0, -1);
	// ft_printtab(map->map);
	ft_printtomlx(map, map->mlx, map->data);
	return (0);
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp temp;

	if (initmlx(map, mlx, data, &temp))
		return (1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, temp.img, 0, 0);
	mlx_key_hook(mlx->win, &move, map);
	ft_printtomlx(map, mlx, data);
	mlx_loop(mlx->mlx);
	mlx_destroy_image(mlx->mlx, temp.img);
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