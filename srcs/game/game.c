/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/14 03:23:17 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_text(t_plane *plane)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(plane->texture[i]);
	free(plane->texture);
}

void	destroywindows(t_mlx *mlx, t_map *map)
{
	mlx_destroy_image(mlx->mlx, map->img.img);
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_text(map->plane);
	free(mlx->mlx);
	free(map->plane);
	free(map->press);
	free(map->temp);
}

int	ft_close(t_map *map)
{
	mlx_loop_end(map->mlx->mlx);
	return (1);
}


int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	(void)data;
	map->temp = ft_calloc(sizeof(t_temp), 1);
	map->plane = ft_calloc(sizeof(t_plane), 1);
	map->press = ft_calloc(sizeof(t_press), 1);
	if (initmlx(map, mlx))
		return (1);
	init_plane(map->plane, map);
	init_buff(map->plane);
	load_texture(map);
	draw_rayons_all(map, map->plane);
	mlx_loop_hook(mlx->mlx, &move, map);
	mlx_hook(mlx->win, 2, 1L << 0, &key_press, map);
	mlx_hook(mlx->win, 3, 1L << 1, &key_release, map);
	mlx_hook(mlx->win, 17, 0, &ft_close, map);
	mlx_loop(mlx->mlx);
	destroywindows(mlx, map);
	return (0);
}

/*

ETAPE 1: mini so long

ETAPE 2: tourner camera

ETAPE 3: ligne de 10pixel bien droit 

ETAPE 4: la ligne doit mtn sarreter au 1er mur

ETAPE 5: ligne x fov




*/