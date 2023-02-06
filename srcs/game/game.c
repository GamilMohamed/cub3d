/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/06 08:08:57 by mgamil           ###   ########.fr       */
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

void	destroywindows(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp	temp;
	int r;

	map->mini = ft_calloc(sizeof(t_temp), 1);
	if (initmlx(map, mlx, data, &temp))
		return (1);
	r = 0;
	map->nbrayons = 2;
	init_minimap(map, mlx, data);
	fill_minimap(map, mlx, data);
	mlx_put_image_to_window(mlx->mlx, mlx->win, temp.img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, map->mlx->win, map->mini->img, 35, 35);
	// mlx_hook(mlx->win, KeyPress, KeyPressMask, key_press, map);
	// mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, key_release, map);
	// mlx_key_hook(mlx->win, key_press, (void *)0);
	// mlx_key_release_hook(mlx->win, key_release, (void *)0);
	mlx_key_hook(mlx->win, &move, map);
	mlx_hook(mlx->win, r, KeyPressMask, &move, data);
	mlx_loop(mlx->mlx);
	mlx_destroy_image(mlx->mlx, temp.img);
	mlx_destroy_image(mlx->mlx, map->mini->img);
	free(map->mini);
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