/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/11 04:47:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotation(t_map *map, t_plane *p, int axis)
{
	double	rot;
	double	olddir;
	double	oldplane;

	rot = p->rotSpeed;
	if (axis)
		rot = -p->rotSpeed;
	olddir = p->dir.x;
	p->dir.x = p->dir.x * cos(rot) - p->dir.y * sin(rot);
	p->dir.y = olddir * sin(rot) + p->dir.y * cos(rot);
	oldplane = p->plane.x;
	p->plane.x = p->plane.x * cos(rot) - p->plane.y * sin(rot);
	p->plane.y = oldplane * sin(rot) + p->plane.y * cos(rot);
}

void	direction_ns(t_map *map, t_plane *p, int dir)
{
	if (dir == 1)
	{
		if (map->map[(int)(p->pos.x + p->moveSpeed
				* p->dir.x)][(int)(p->pos.y)] == '0')
			p->pos.x += p->dir.x * p->moveSpeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->moveSpeed
				* p->dir.y)] == '0')
			p->pos.y += p->dir.y * p->moveSpeed;
	}
	if (dir == 2)
	{
		if (map->map[(int)(p->pos.x - p->moveSpeed
				* p->dir.x)][(int)(p->pos.y)] == '0')
			p->pos.x -= p->dir.x * p->moveSpeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->moveSpeed
				* p->dir.y)] == '0')
			p->pos.y -= p->dir.y * p->moveSpeed;
	}
}

void	direction_we(t_map *map, t_plane *p, int dir)
{
	if (dir == 1)
	{
		if (map->map[(int)(p->pos.x - p->dir.y
				* p->moveSpeed)][(int)(p->pos.y)] == '0')
			p->pos.x -= p->dir.y * p->moveSpeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x
				* p->moveSpeed)] == '0')
			p->pos.y += p->dir.x * p->moveSpeed;
	}
	if (dir == 2)
	{
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x
				* p->moveSpeed)] == '0')
			p->pos.y -= p->dir.x * p->moveSpeed;
		if (map->map[(int)(p->pos.x + p->dir.y
				* p->moveSpeed)][(int)(p->pos.y)] == '0')
			p->pos.x += p->dir.y * p->moveSpeed;
	}
}

int	move(t_map *map)
{
	t_plane	*p;

	p = map->plane;
	if (map->press->w == 1)
		direction_ns(map, p, 1);
	if (map->press->s == 1)
		direction_ns(map, p, 2);
	if (map->press->a == 1)
		direction_we(map, p, 1);
	if (map->press->d == 1)
		direction_we(map, p, 2);
	if (map->press->right == 1)
		rotation(map, map->plane, 1);
	if (map->press->left == 1)
		rotation(map, map->plane, 0);
	if (map->press->esc == 1)
		mlx_loop_end(map->mlx->mlx);
	draw_rayons_all(map, map->temp, map->plane);
	draw(map);
	return (0);
}
