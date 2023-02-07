/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/07 03:30:36 by mgamil           ###   ########.fr       */
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
	if (map->map[(int)(temp.y + (norm.y * 10))/35][(int)(temp.x + (norm.x * 10))/35] == '1')
			return ;
	// if (map->map[(int)((temp.y + 5) + (norm.y * 20))/35][(int)(temp.x + (norm.x * 20))/35] == '1' && map->map[(int)((temp.y) + (norm.y * 20))/35][(int)((temp.x + 5) + (norm.x * 20))/35])
	// 	return ;
	map->mini->coords = (map->mini->coords + norm * 10);
	pos = convert_d_to_i(temp);
	map->map[pos.y/35][pos.x/35] = '0';
}

// void	move(mlx_key_data_t key, void *ptr)
// {
// 	t_map *map;

// 	map = ptr;
// 	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		mlx_terminate(map->mlx->mlx);
// 	else if (key.key == MLX_KEY_W && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		move_to_pos(map, normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
// 	else if (key.key == MLX_KEY_S && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		move_to_pos(map, -normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
// 	else if (key.key == MLX_KEY_D && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		move_to_pos(map, -normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
// 	else if (key.key == MLX_KEY_A && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		move_to_pos(map, normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
// 	else if (key.key == MLX_KEY_LEFT && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		map->rotation -= 15;
// 	else if (key.key == MLX_KEY_RIGHT && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		map->rotation += 15;
// 	else if (key.key == MLX_KEY_UP && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		map->nbrayons += 10;
// 	else if (key.key == MLX_KEY_DOWN && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
// 		map->nbrayons -= 10;
// 	if (map->rotation >= 360)
// 		map->rotation = 0;
// 	// fill_minimap(map, map->mlx, map->data);
// 	// mlx_image_to_window(map->mlx->mlx, map->mini->img, 35, 35);
// }
