/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/08 06:22:10 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	direction_zero(t_plane *plane, char player)
{
	if (player == 'N' || player == 'S')
	{
		plane->dir.y = 0;
		plane->plane.x = 0;
	}
	else if (player == 'E' || player == 'W')
	{
		plane->dir.x = 0;
		plane->plane.y = 0;
	}
}

void	orientation_player(t_plane *plane, char player)
{
	if (player == 'N')
	{
		plane->dir.x = -1;
		plane->plane.y = 0.66;
	}
	else if (player == 'S')
	{
		plane->dir.x = 1;
		plane->plane.y = -0.66;
	}
	else if (player == 'E')
	{
		plane->dir.y = 1;
		plane->plane.x = 0.66;
	}
	else if (player == 'W')
	{
		plane->dir.y = -1;
		plane->plane.x = -0.66;
	}
	direction_zero(plane, player);
}

void print_to_map(t_map *map)
{
	// map_to_minimap(map, map->data, map->mini, map->mini->size);
	camera_rays(map->mini, map, map->mini->coords, map->mini->size / 2);
}

void    destroywindows(t_mlx *mlx)
{
    mlx_clear_window(mlx->mlx, mlx->win);
    mlx_destroy_window(mlx->mlx, mlx->win);
    mlx_destroy_display(mlx->mlx);
    free(mlx->mlx);
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	map->temp = ft_calloc(sizeof(t_temp), 1);
	map->mini = ft_calloc(sizeof(t_temp), 1);
	map->plane = ft_calloc(sizeof(t_plane), 1);
	if (initmlx(map, mlx, data, map->temp))
		return (1);
	map->plane->moveSpeed = 0.05;
	map->plane->rotSpeed = 0.05;
	map->plane->pos = map->pos;
	orientation_player(map->plane, map->data->player);
	// init_minimap(map, mlx, data);
	print_to_map(map);
	mlx_put_image_to_window(mlx->mlx, mlx->win, map->temp->img, 0, 0);
	// mlx_put_image_to_window(mlx->mlx, mlx->win, map->mini->img, 24, 24);
	// fill_minimap(map, mlx, data);
	mlx_key_hook(mlx->win, &move, map);
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