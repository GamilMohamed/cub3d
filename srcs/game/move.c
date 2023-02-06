/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/06 08:35:25 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_to_pos(t_map *map, Luno2f norm, Luno2f end)
{
	Luno2i pos;
	Luno2f temp;
	Luno2i pos_map;

	// pos_map = convert_d_to_i((temp + (norm * 5)) / 35);
	// if (map->map[pos_map.y][pos_map.x] == '1')  
	temp = map->mini->coords;
	if (map->map[(int)(temp.y + (norm.y * 5))/35][(int)(temp.x + (norm.x * 5))/35] == '1')
			return ;
	map->mini->coords = (map->mini->coords + norm * 5);
	pos = convert_d_to_i(temp);
	map->map[pos.y/35][pos.x/35] = '0';
}

int	move(int key, t_map *map)
{
	if (key == ESCAPE)
		return (mlx_loop_end(map->mlx->mlx));
	else if (key == W)
		move_to_pos(map, normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
	else if (key == S)
		move_to_pos(map, -normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
	else if (key == D)
		move_to_pos(map, -normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
	else if (key == A)
		move_to_pos(map, normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
	else if (key == LEFT)
		map->rotation -= 15;
	else if (key == RIGHT)
		map->rotation += 15;
	else if (key == UP)
		map->nbrayons += 10;
	else if (key == DOWN)
		map->nbrayons -= 10;
	if (map->rotation >= 360)
		map->rotation = 0;
	fill_minimap(map, map->mlx, map->data);
	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->mini->img, 35, 35);
	return (0);
}
