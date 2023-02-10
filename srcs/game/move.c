/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/10 19:10:39 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move(t_map *map)
{
	t_plane *p;

	// printf("movesadasdas key = %i\n", key);
	p = map->plane;
	if (map->press->w == 1)
	{ 
		if (map->map[(int)(p->pos.x + p->moveSpeed * p->dir.x)][(int)(p->pos.y)] == '0')
			p->pos.x += p->dir.x * p->moveSpeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->moveSpeed * p->dir.y)] == '0')
			p->pos.y += p->dir.y * p->moveSpeed;
	}
	if (map->press->s == 1)
	{ 
		if (map->map[(int)(p->pos.x - p->moveSpeed * p->dir.x)][(int)(p->pos.y)] == '0')
			p->pos.x -= p->dir.x * p->moveSpeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->moveSpeed * p->dir.y)] == '0')
			p->pos.y -= p->dir.y * p->moveSpeed;
	}
	if (map->press->a == 1)
	{ 
		if (map->map[(int)(p->pos.x - p->dir.y * p->moveSpeed)][(int)(p->pos.y)] == '0')
			p->pos.x -= p->dir.y * p->moveSpeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x * p->moveSpeed)] == '0')
			p->pos.y += p->dir.x * p->moveSpeed;
	}
	if (map->press->d == 1)
	{ 
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x* p->moveSpeed)] == '0')
			p->pos.y -= p->dir.x * p->moveSpeed;
		if (map->map[(int)(p->pos.x + p->dir.y * p->moveSpeed)][(int)(p->pos.y)] == '0')
			p->pos.x += p->dir.y * p->moveSpeed;
		// if (map->map[(int)(p->pos.y + p->moveSpeed * p->dir.x * sqrt(0.19))][(int)(p->pos.x)] == '0')
		// 	p->pos.y += p->dir.x * sqrt(0.19) * p->moveSpeed;
		// if (map->map[(int)(p->pos.y)][(int)(p->pos.x - p->moveSpeed * 0.9 * p->dir.y)] == '0')
		// 	p->pos.x -= 0.9 * p->dir.y * p->moveSpeed;
	}
	if (map->press->right == 1)
	{
		double oldDirx = p->dir.x;
		p->dir.x = p->dir.x * cos(-p->rotSpeed) - p->dir.y * sin(-p->rotSpeed);
		p->dir.y = oldDirx * sin(-p->rotSpeed) + p->dir.y * cos(-p->rotSpeed);
		double oldPlanex = p->plane.x;
		p->plane.x = p->plane.x * cos(-p->rotSpeed) - p->plane.y * sin(-p->rotSpeed);
		p->plane.y = oldPlanex * sin(-p->rotSpeed) + p->plane.y * cos(-p->rotSpeed);
	}
	if (map->press->left == 1)
	{
		double oldDirx = p->dir.x;
		p->dir.x = p->dir.x * cos(p->rotSpeed) - p->dir.y * sin(p->rotSpeed);
		p->dir.y = oldDirx * sin(p->rotSpeed) + p->dir.y * cos(p->rotSpeed);
		double oldPlanex = p->plane.x;
		p->plane.x = p->plane.x * cos(p->rotSpeed) - p->plane.y * sin(p->rotSpeed);
		p->plane.y = oldPlanex * sin(p->rotSpeed) + p->plane.y * cos(p->rotSpeed);
	}
	if (map->press->esc == 1)
		mlx_loop_end(map->mlx->mlx);
	if (map->press->z == 1)
	{
		printf("pos %f|%f\n",(p->pos.y),(p->pos.x));
		printf("dor %f|%f\n",(p->dir.y),(p->dir.x));
	}
	draw_rayons_all(map, map->temp, map->plane);
	draw(map);
	// mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->img.img, 0, 0);
	return (0);
}



// int	move(int key, t_map *map)
// {
// 	t_plane *p;

// 	p = map->plane;
// 	if (key == W)
// 	{
// 		if (map->map[(int)(p->pos.y + p->dir.y * p->moveSpeed)][(int)(p->pos.x)] == '0')
// 			p->pos.y += p->dir.y * p->moveSpeed;
// 		if (map->map[(int)(p->pos.y)][(int)(p->pos.x + p->dir.x * p->moveSpeed)] == '0')
// 			p->pos.x += p->dir.x * p->moveSpeed;
// 	}
// 	if (key == S)
// 	{
// 		if (map->map[(int)(p->pos.y - p->dir.y * p->moveSpeed)][(int)(p->pos.x)] == '0')
// 			p->pos.y -= p->dir.y * p->moveSpeed;
// 		if (map->map[(int)(p->pos.y)][(int)(map->pos.x - p->dir.x * p->moveSpeed)] == '0')
// 			p->pos.x -= p->dir.x * p->moveSpeed;
// 	}
// 	// if (key == D)
// 	// {
// 	// 	if (map->map[(int)(p->pos.y - p->dir.x * p->moveSpeed)][(int)(p->pos.x)] == '0')
// 	// 		p->pos.y -= p->dir.x * p->moveSpeed;
// 	// 	if (map->map[(int)(p->pos.y)][(int)(map->pos.x - p->dir.y * p->moveSpeed)] == '0')
// 	// 		p->pos.x -= p->dir.y * p->moveSpeed;	
// 	// }
// 	// if (key == A)
// 	// {
// 	// 	if (map->map[(int)(p->pos.y + p->dir.x * p->moveSpeed)][(int)(p->pos.x)] == '0')
// 	// 		p->pos.y += p->dir.x * p->moveSpeed;
// 	// 	if (map->map[(int)(p->pos.y)][(int)(p->pos.x + p->dir.y * p->moveSpeed)] == '0')
// 	// 		p->pos.x += p->dir.y * p->moveSpeed;
// 	// }
// 	if (key == RIGHT)
// 	{
// 		double oldDirx = p->dir.x;
// 		p->dir.x = p->dir.x * cos(-p->rotSpeed) - p->dir.y * sin(-p->rotSpeed);
// 		p->dir.y = oldDirx * sin(-p->rotSpeed) + p->dir.y * cos(-p->rotSpeed);
// 		// double oldPlanex = p->plane.x;
// 		// p->plane.x = p->plane.x * cos(-p->rotSpeed) - p->plane.y * sin(-p->rotSpeed);
// 		// p->plane.y = oldPlanex * sin(-p->rotSpeed) + p->plane.y * cos(-p->rotSpeed);
// 	}
// 	if (key == LEFT)
// 	{
// 		double oldDirx = p->dir.x;
// 		p->dir.x = p->dir.x * cos(p->rotSpeed) - p->dir.y * sin(p->rotSpeed);
// 		p->dir.y = oldDirx * sin(p->rotSpeed) + p->dir.y * cos(p->rotSpeed);
// 		double oldPlanex = p->plane.x;
// 		p->plane.x = p->plane.x * cos(p->rotSpeed) - p->plane.y * sin(p->rotSpeed);
// 		p->plane.y = oldPlanex * sin(p->rotSpeed) + p->plane.y * cos(p->rotSpeed);
// 	}
// 	if (key == ESCAPE)
// 		mlx_loop_end(map->mlx->mlx);
// 	if (key == 'z')
// 	{
// 		printf("dir-> x:%f|y:%f\n", p->dir.x, p->dir.y);
// 		printf("pos-> x:%f|y:%f\n\n", p->pos.x, p->pos.y);
// 		// ft_printf("%r*****%0\n");

// 	}

// 	print_to_map(map);	
// 	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->temp->img, 0, 0);
// 	// mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->mini->img, 24, 24);
// 	return (0);
// }


// void	move_to_pos(t_map *map, Luno2f norm, Luno2f end)
// {
// 	Luno2i pos;
// 	Luno2f temp;
// 	Luno2i pos_map;

// 	// pos_map = convert_d_to_i((temp + (norm * 5)) / 24);
// 	// if (map->map[pos_map.y][pos_map.x] == '1')
// 	// printf("%p, %p\n", map, map->map);
// 	temp = map->mini->coords;
// 	// printf("%p\n", map->mini);
// 	if (map->map[(int)(temp.y + (norm.y * 10))/24][(int)(temp.x + (norm.x * 10))/24] == '1')
// 			return ;
// 	// if (map->map[(int)((temp.y + 5) + (norm.y * 20))/24][(int)(temp.x + (norm.x * 20))/24] == '1' && map->map[(int)((temp.y) + (norm.y * 20))/24][(int)((temp.x + 5) + (norm.x * 20))/24])
// 	// 	return ;
// 	map->mini->coords = (map->mini->coords + norm * 10);
// 	pos = convert_d_to_i(temp);
// 	map->map[pos.y/24][pos.x/24] = '0';
// }

// int	move(int key, t_map *map)
// {
// 	if (key == ESCAPE)
// 		mlx_loop_end(map->mlx->mlx);
// 	else if (key == W)
// 		move_to_pos(map, normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
// 	else if (key == S)
// 		move_to_pos(map, -normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
// 	else if (key == D)
// 		move_to_pos(map, -normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
// 	else if (key == A)
// 		move_to_pos(map, normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
// 	else if (key == LEFT)
// 		map->rotation -= 15;
// 	else if (key == RIGHT)
// 		map->rotation += 15;
// 	else if (key == UP)
// 		map->nbrayons += 10;
// 	else if (key == DOWN)
// 		map->nbrayons -= 10;
// 	if (map->rotation >= 360)
// 		map->rotation = 0;
// 	print_to_map(map);
// 	// fill_minimap(map, map->mlx, map->data);
// 	// printf("%p, %p, %p\n", map->mlx->mlx, map->mlx->win, map->mini->img);
// 	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->mini->img, 24, 24);
// }
