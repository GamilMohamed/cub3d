/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 04:47:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/14 06:09:51 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	if (keycode == 'h')
		map->press->h = 2;
	// if (keycode == ' ')
	// 	map->press->door = 2;
	if (keycode == ESCAPE || keycode == 'q')
		map->press->esc = 2;
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
	if (keycode == 'h')
		map->press->h = 1;
	// if (keycode == ' ')
	// 	map->press->door = 1;
	if (keycode == ESCAPE || keycode == 'q')
		map->press->esc = 1;
	return (0);
}
