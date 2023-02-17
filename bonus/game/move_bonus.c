/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:07:38 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/17 10:34:38 by mgamil           ###   ########.fr       */
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
					* p->dir.x)][(int)(p->pos.y)] == '0')
			|| (map->map[(int)(p->pos.x + p->movespeed
					* p->dir.x)][(int)(p->pos.y)] == 'C'))
			p->pos.x += p->dir.x * p->movespeed;
		if ((map->map[(int)(p->pos.x)][(int)(p->pos.y + p->movespeed
					* p->dir.y)] == '0')
			|| (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->movespeed
					* p->dir.y)] == 'C'))
			p->pos.y += p->dir.y * p->movespeed;
		return ;
	}
	if ((map->map[(int)(p->pos.x - p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == '0')
		|| (map->map[(int)(p->pos.x - p->movespeed
				* p->dir.x)][(int)(p->pos.y)] == 'C'))
		p->pos.x -= p->dir.x * p->movespeed;
	if ((map->map[(int)(p->pos.x)][(int)(p->pos.y - p->movespeed
				* p->dir.y)] == '0')
		|| (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->movespeed
				* p->dir.y)] == 'C'))
		p->pos.y -= p->dir.y * p->movespeed;
}

void	direction_we(t_map *map, t_plane *p, int dir)
{
	if (dir == 1)
	{
		if ((map->map[(int)(p->pos.x - p->dir.y
					* p->movespeed)][(int)(p->pos.y)] == '0')
			|| (map->map[(int)(p->pos.x - p->dir.y
					* p->movespeed)][(int)(p->pos.y)] == 'C'))
			p->pos.x -= p->dir.y * p->movespeed;
		if ((map->map[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x
					* p->movespeed)] == '0')
			|| (map->map[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x
					* p->movespeed)] == 'C'))
			p->pos.y += p->dir.x * p->movespeed;
		return ;
	}
	if ((map->map[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x
				* p->movespeed)] == '0')
		|| (map->map[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x
				* p->movespeed)] == 'C'))
		p->pos.y -= p->dir.x * p->movespeed;
	if ((map->map[(int)(p->pos.x + p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == '0')
		|| (map->map[(int)(p->pos.x + p->dir.y
				* p->movespeed)][(int)(p->pos.y)] == 'C'))
		p->pos.x += p->dir.y * p->movespeed;
}

#define SECOND 1

t_luno2f	day_night(t_map *map)
{
	static double	max;
	static double	r;
	double			time;
	static double	d;
	static int		stop;

	draw_rayons_all(map, map->plane, max, ((r / 2) * 64 / 510));
	if (stop)
		max -= SECOND;
	if (!stop)
		max += SECOND;
	if (max == 510)
		stop = 1;
	else if (max == 0)
		stop = 0;
	r += SECOND;
	time = r / 42.5;
	if (time == 24)
	{
		r = 0;
		if (++d == 1023)
			d = 0;
	}
	return ((t_luno2f){time, d});
}

void	door(t_map *map, t_plane *p, char src, char dst)
{
	int	x;
	int	y;

	x = p->pos.x;
	y = p->pos.y;
	if (map->map[x][y + 1] == src)
		map->map[x][y + 1] = dst;
	else if (map->map[x][y - 1] == src)
		map->map[x][y - 1] = dst;
	else if (map->map[x - 1][y] == src)
		map->map[x - 1][y] = dst;
	else if (map->map[x + 1][y] == src)
		map->map[x + 1][y] = dst;
	else if (map->map[x][y] == src)
		map->map[x][y] = dst;
	map->press->door = 0;
}

void	print_time(t_mlx *mlx, t_luno2f time)
{
	char	buff[1024];

	mlx_string_put(mlx->mlx, mlx->win, 10, HEIGHT - 10, 16777215,
			"press h for help");
	ft_strcpy(buff, "day: ");
	ft_stoval(buff, time.y, 5, 5 + lenof(time.y));
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 110, HEIGHT - 10, 16777215,
			buff);
	ft_stoval(buff, time.x, 0, lenof(time.x));
	ft_strcat(buff, "h");
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 60, HEIGHT - 10, 16777215, buff);
}

int	move(t_map *map)
{
	t_plane		*p;
	t_luno2f	time;

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
		door(map, p, 'D', 'C');
	if (map->press->door == 1)
		door(map, p, 'C', 'D');
	if (map->press->esc == 1)
		mlx_loop_end(map->mlx->mlx);
	time = day_night(map);
	if (map->press->h == 1)
		print_help(map, &map->help);
	if (map->press->m == 2)
		fill_minimap(map, map->mlx);
	draw(map);
	print_time(map->mlx, time);
	return (0);
}

/*

0 = nuit, 510 = midi, 255 = 12h


510 = 24h
510 / 24 = 1h
510 / 24 / 60 = 1min
510 / 24 / 60 / 60 = 1s


*/