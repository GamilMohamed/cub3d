/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/14 16:09:40 by mgamil           ###   ########.fr       */
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
		if ((map->map[(int)(p->pos.x + p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == '0') || (map->map[(int)(p->pos.x + p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == 'C'))
			p->pos.x += p->dir.x * p->movespeed;
		if ((map->map[(int)(p->pos.x)][(int)(p->pos.y + p->movespeed
				* p->dir.y)] == '0') || (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->movespeed
				* p->dir.y)] == 'C'))
			p->pos.y += p->dir.y * p->movespeed;
	}
	if (dir == 2)
	{
		if ((map->map[(int)(p->pos.x - p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == '0') || (map->map[(int)(p->pos.x - p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == 'C'))
			p->pos.x -= p->dir.x * p->movespeed;
		if ((map->map[(int)(p->pos.x)][(int)(p->pos.y - p->movespeed
				* p->dir.y)] == '0') || (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->movespeed
				* p->dir.y)] == 'C'))
			p->pos.y -= p->dir.y * p->movespeed;
	}
}

void	direction_we(t_map *map, t_plane *p, int dir)
{
	if (dir == 1)
	{
		if ((map->map[(int)(p->pos.x - p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == '0') || (map->map[(int)(p->pos.x - p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == 'C'))
			p->pos.x -= p->dir.y * p->movespeed;
		if ((map->map[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x
				* p->movespeed)] == '0') || (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x
				* p->movespeed)] == 'C'))
			p->pos.y += p->dir.x * p->movespeed;
	}
	if (dir == 2)
	{
		if ((map->map[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x
				* p->movespeed)] == '0') || (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x
				* p->movespeed)] == 'C'))
			p->pos.y -= p->dir.x * p->movespeed;
		if ((map->map[(int)(p->pos.x + p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == '0') || (map->map[(int)(p->pos.x + p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == 'C'))
			p->pos.x += p->dir.y * p->movespeed;
	}
}

#define SECOND 0.5

void	day_night(t_map *map)
{
	static	double	max;
	static	double	r;
	static	double	d;
	static	int		stop;
	if (stop)
	{
		draw_rayons_all(map, map->plane, max);
		if (max == 0)
			stop = 0;
		max -= SECOND;
	}
	if (!stop)
	{
		draw_rayons_all(map, map->plane, max);
		if (max == 510)
			stop = 1;
		max += SECOND;
	}
	r += SECOND;
	draw(map);
	mlx_string_put(map->mlx->mlx, map->mlx->win, 10, HEIGHT - 10, 0x00FFFFFF, "press h for help");
	mlx_string_put(map->mlx->mlx, map->mlx->win, WIDTH - 110, HEIGHT - 10, 0x00FFFFFF, ft_strjoin("jour: ", ft_itoa(d)));
	mlx_string_put(map->mlx->mlx, map->mlx->win, WIDTH - 60, HEIGHT - 10, 0x00FFFFFF, ft_strjoin(ft_itoa(r / 42.5), "h"));
	if (r / 42.5 == 24)
	{
		r = 0;
		d++;
	}
}

void close_door(t_map *map)
{
	t_plane *p;

	p = map->plane;

	if (map->map[(int)map->plane->pos.x][(int)map->plane->pos.y + 1] == 'C')
	{
		map->map[(int)map->plane->pos.x][(int)map->plane->pos.y + 1] = 'D';
		map->press->door = 0;
	}
	else if (map->map[(int)map->plane->pos.x][(int)map->plane->pos.y - 1] == 'C')
	{
		map->map[(int)map->plane->pos.x][(int)map->plane->pos.y - 1] = 'D';
		map->press->door = 0;	
	}
	else if (map->map[(int)map->plane->pos.x - 1][(int)map->plane->pos.y] == 'C')
	{
		map->map[(int)map->plane->pos.x - 1][(int)map->plane->pos.y] = 'D';
		map->press->door = 0;	
	}
	else if (map->map[(int)map->plane->pos.x + 1][(int)map->plane->pos.y] == 'C')
	{
		map->map[(int)map->plane->pos.x + 1][(int)map->plane->pos.y] = 'D';
		map->press->door = 0;	
	}

}
void open_door(t_map *map)
{
	t_plane *p;

	p = map->plane;
	if (map->map[(int)map->plane->pos.x][(int)map->plane->pos.y + 1] == 'D')
	{
		map->map[(int)map->plane->pos.x][(int)map->plane->pos.y + 1] = 'C';
		map->press->door = 0;
	}
	else if (map->map[(int)map->plane->pos.x][(int)map->plane->pos.y - 1] == 'D')
	{
		map->map[(int)map->plane->pos.x][(int)map->plane->pos.y - 1] = 'C';
		map->press->door = 0;
	}
	else if (map->map[(int)map->plane->pos.x - 1][(int)map->plane->pos.y] == 'D')
	{
		map->map[(int)map->plane->pos.x - 1][(int)map->plane->pos.y] = 'C';
		map->press->door = 0;
	}
	else if (map->map[(int)map->plane->pos.x + 1][(int)map->plane->pos.y] == 'D')
	{
		map->map[(int)map->plane->pos.x + 1][(int)map->plane->pos.y] = 'C';
		map->press->door = 0;
	}
	else
	{
		map->press->door = 1;
	}
}
	

int	move(t_map *map)
{
	t_plane		*p;

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
	if (map->press->door == 2)
		open_door(map);
	if (map->press->door == 1)
		close_door(map);
	if (map->press->esc == 1)
		mlx_loop_end(map->mlx->mlx);
	day_night(map);
	// p->door = 0;
	if (map->press->m == 2)
	{
		fill_minimap(map, map->mlx,	map->data);
		mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->mini->img, 10, 10);
		p->door = 1;
	}
	if (map->press->h == 1)
		mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->help.img, WIDTH / 4, HEIGHT / 4);
	return (0);
}

/*

0 = nuit, 510 = midi, 255 = 12h


510 = 24h
510 / 24 = 1h
510 / 24 / 60 = 1min
510 / 24 / 60 / 60 = 1s


*/