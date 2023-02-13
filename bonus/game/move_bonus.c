/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/13 06:05:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	t_plane		*p;
	static int	max;
	static int	r;
	static int	stop;

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
	if (stop)
	{
		draw_rayons_all(map, map->plane, --max);
		if (max == 0)
			stop = 0;
	}
	if (!stop)
	{
		draw_rayons_all(map, map->plane, ++max);
		if (max == 510)
			stop = 1;
	}
	r += map->press->m;
	draw(map);
	if (map->press->m == 2)
	{
		fill_minimap(map, map->mlx,	map->data);
		mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->mini->img, 10, 10);
	}
	if (map->press->h == 1)
		mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->help.img, WIDTH / 4, HEIGHT / 4);
	mlx_string_put(map->mlx->mlx, map->mlx->win, 10, HEIGHT - 10, 0x00FFFFFF, "press h for help");
	return (0);
}


/*



510 = 24h
510 / 24 = 1h
510 / 24 / 60 = 1min
510 / 24 / 60 / 60 = 1s


*/