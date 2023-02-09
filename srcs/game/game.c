/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/09 18:54:11 by mgamil           ###   ########.fr       */
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

void	orientation_player(t_plane *plane, char player)
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

void print_to_map(t_map *map)
{
	camera_rays(map->mini, map, map->mini->coords, map->mini->size / 2);
	map_to_minimap(map, map->data, map->mini, map->mini->size);
}

void    destroywindows(t_mlx *mlx)
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

int		key_press(int keycode, t_map *map)
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

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	map->temp = ft_calloc(sizeof(t_temp), 1);
	map->mini = ft_calloc(sizeof(t_temp), 1);
	map->plane = ft_calloc(sizeof(t_plane), 1);
	map->press = ft_calloc(sizeof(t_press), 1);
	if (initmlx(map, mlx, data, map->temp))
		return (1);
	orientation_player(map->plane, map->data->player);
	map->plane->plane.x = 0.66 * (-1 *  map->plane->dir.y);
	map->plane->plane.y = 0.66 * (-1 * map->plane->dir.x);
	map->plane->moveSpeed = 0.05;
	map->plane->rotSpeed = 0.01;
	map->plane->pos = map->pos;
	
	// init_minimap(map, mlx, data);
	print_to_map(map);
	mlx_put_image_to_window(mlx->mlx, mlx->win, map->temp->img, 0, 0);
	// mlx_put_image_to_window(mlx->mlx, mlx->win, map->mini->img, 24, 24);
	// fill_minimap(map, mlx, data);
	mlx_loop_hook(mlx->mlx, &move, map);
	mlx_hook(mlx->win, 2, 1L << 0, &key_press, map);
	mlx_hook(mlx->win, 3, 1L << 1, &key_release, map);
	mlx_loop(mlx->mlx);
	mlx_destroy_image(mlx->mlx, map->temp->img);
	// mlx_destroy_image(mlx->mlx, map->mini->img);
	destroywindows(mlx);
	free(map->mini);
	free(map->plane);
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