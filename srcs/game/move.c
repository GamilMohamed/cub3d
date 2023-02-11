/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/11 21:10:31 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotation(t_plane *p, int axis)
{
	double	rot;
	double	olddir;
	double	oldplane;

	rot = p->rotspeed;
	if (axis)
		rot = -p->rotspeed;
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
		if (map->map[(int)(p->pos.x + p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == '0')
			p->pos.x += p->dir.x * p->movespeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->movespeed
				* p->dir.y)] == '0')
			p->pos.y += p->dir.y * p->movespeed;
	}
	if (dir == 2)
	{
		if (map->map[(int)(p->pos.x - p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == '0')
			p->pos.x -= p->dir.x * p->movespeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->movespeed
				* p->dir.y)] == '0')
			p->pos.y -= p->dir.y * p->movespeed;
	}
}

void	direction_we(t_map *map, t_plane *p, int dir)
{
	if (dir == 1)
	{
		if (map->map[(int)(p->pos.x - p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == '0')
			p->pos.x -= p->dir.y * p->movespeed;
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x
				* p->movespeed)] == '0')
			p->pos.y += p->dir.x * p->movespeed;
	}
	if (dir == 2)
	{
		if (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x
				* p->movespeed)] == '0')
			p->pos.y -= p->dir.x * p->movespeed;
		if (map->map[(int)(p->pos.x + p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == '0')
			p->pos.x += p->dir.y * p->movespeed;
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
		rotation(map->plane, 1);
	if (map->press->left == 1)
		rotation(map->plane, 0);
	if (map->press->esc == 1)
		mlx_loop_end(map->mlx->mlx);
	draw_rayons_all(map, map->plane);
	draw(map);
	return (0);
}
