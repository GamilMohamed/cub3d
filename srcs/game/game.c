/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/10 02:59:48 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	direction_zero(t_plane *plane, char player)
{
	if (player == 'N' || player == 'S')
	{
		plane->dir.y = 0;
		plane->plane.x = 0.66;
	}
	else if (player == 'E' || player == 'W')
	{
		plane->dir.x = 0;
		plane->plane.y = 0.66;
	}
}

void	orientation(t_plane *plane, char player)
{
	if (player == 'N')
	{
		plane->dir.x = 0;
		plane->dir.y = -1;
	}
	else if (player == 'S')
	{
		plane->dir.x = 0;
		plane->dir.y = 1;
	}
	else if (player == 'E')
	{
		plane->dir.x = 1;
		plane->dir.y = 0;
	}
	else if (player == 'W')
	{
		plane->dir.x = -1;
		plane->dir.y = 0;
	}
	//direction_zero(plane, player);
}

void	destroywindows(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

int	key_release(int keycode, t_map *map)
{
	if (keycode == W)
		map->press->w = 2;
	if (keycode == S)
		map->press->s = 2;
	if (keycode == A)
		map->press->a = 2;
	if (keycode == D)
		map->press->d = 2;
	if (keycode == LEFT)
		map->press->left = 2;
	if (keycode == RIGHT)
		map->press->right = 2;
	if (keycode == ESCAPE)
		map->press->esc = 2;
	if (keycode == 'z')
		map->press->z = 2;
	return (0);
}

int	key_press(int keycode, t_map *map)
{
	if (keycode == W)
		map->press->w = 1;
	if (keycode == S)
		map->press->s = 1;
	if (keycode == A)
		map->press->a = 1;
	if (keycode == D)
		map->press->d = 1;
	if (keycode == LEFT)
		map->press->left = 1;
	if (keycode == RIGHT)
		map->press->right = 1;
	if (keycode == ESCAPE)
		map->press->esc = 1;
	if (keycode == 'z')
		map->press->z = 1;
	return (0);
}

void	load_image(t_map *map, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(map->mlx->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(map->mlx->mlx, img->img);
}

void	draw(t_map *map)
{
	for (int y = 0; y < map->data->win_h; y++)
	{
		for (int x = 0; x < map->data->win_w; x++)
		{
			map->temp->addr[y * map->data->win_w + x] = map->plane->buff[y][x];
		}
	}
	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->temp->img, 0, 0);
}

void	load_texture(t_map *map)
{
	t_img	img;

	load_image(map, map->plane->texture[0], "./s/brick2.xpm", &img);
	load_image(map, map->plane->texture[1], "./s/brick2.xpm", &img);
	load_image(map, map->plane->texture[2], "./s/brick2.xpm", &img);
	load_image(map, map->plane->texture[3], "./s/brick2.xpm", &img);
}

void	init_buff(t_plane *p, t_map *map)
{
	for (int i = 0; i < map->data->win_h; i++)
	{
		for (int j = 0; j < map->data->win_w; j++)
		{
			p->buff[i][j] = 0;
		}
	}
	p->texture = (int **)malloc(sizeof(int *) * 4 * 4);
	for (int i = 0; i < 4; i++)
	{
		p->texture[i] = (int *)malloc(sizeof(int) * (64 * 640));
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < (64 * 64 * 4); j++)
		{
			p->texture[i][j] = 0;
		}
	}
}

void	init_plane(t_plane *plane, t_map *map)
{
	orientation(plane, map->data->player);
	plane->plane.x = 0.66 * (-1 * plane->dir.y);
	plane->plane.y = 0.66 * (-1 * plane->dir.x);
	plane->moveSpeed = 0.05;
	plane->rotSpeed = 0.05;
	plane->pos = map->pos;
	plane->re_buf = 0;
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	map->temp = ft_calloc(sizeof(t_temp), 1);
	map->plane = ft_calloc(sizeof(t_plane), 1);
	map->press = ft_calloc(sizeof(t_press), 1);
	if (initmlx(map, mlx, data, map->temp))
		return (1);
	init_plane(map->plane, map);
	init_buff(map->plane, map);
	load_texture(map);
	draw_rayons_all(map, map->temp, map->plane);
	// mlx_put_image_to_window(mlx->mlx, mlx->win, map->temp->img, 0, 0);
	mlx_loop_hook(mlx->mlx, &move, map);
	mlx_hook(mlx->win, 2, 1L << 0, &key_press, map);
	mlx_hook(mlx->win, 3, 1L << 1, &key_release, map);
	mlx_loop(mlx->mlx);
	mlx_destroy_image(mlx->mlx, map->temp->img);
	destroywindows(mlx);
	free(map->plane);
	free(map->press);
	free(map->temp);
	return (0);
}

/*

ETAPE 1: mini so long

ETAPE 2: tourner camera

ETAPE 3: ligne de 10pixel bien droit 

ETAPE 4: la ligne doit mtn sarreter au 1er mur

ETAPE 5: ligne x fov




*/