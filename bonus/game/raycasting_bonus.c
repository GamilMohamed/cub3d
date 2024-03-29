/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:06:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/18 04:13:00 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_cast(t_plane *plane, int index)
{
	plane->camera.x = 2 * index / (double)WIDTH - 1;
	plane->raydir.x = plane->dir.x + plane->plane.x * plane->camera.x;
	plane->raydir.y = plane->dir.y + plane->plane.y * plane->camera.x;
	plane->map.x = (int)plane->pos.x;
	plane->map.y = (int)plane->pos.y;
	plane->deltadist.x = fabs(1 / plane->raydir.x);
	plane->deltadist.y = fabs(1 / plane->raydir.y);
	plane->hit = 0;
}

void	init_steps(t_plane *p)
{
	if (p->raydir.x < 0)
	{
		p->step.x = -1;
		p->sdist.x = (p->pos.x - p->map.x) * p->deltadist.x;
	}
	else
	{
		p->step.x = 1;
		p->sdist.x = (p->map.x + 1.0 - p->pos.x) * p->deltadist.x;
	}
	if (p->raydir.y < 0)
	{
		p->step.y = -1;
		p->sdist.y = (p->pos.y - p->map.y) * p->deltadist.y;
	}
	else
	{
		p->step.y = 1;
		p->sdist.y = (p->map.y + 1.0 - p->pos.y) * p->deltadist.y;
	}
}

void	dda(t_map *map, t_plane *p)
{
	while (p->hit == 0)
	{
		if (p->sdist.x < p->sdist.y)
		{
			p->sdist.x += p->deltadist.x;
			p->map.x += p->step.x;
			p->side = 0;
		}
		else
		{
			p->sdist.y += p->deltadist.y;
			p->map.y += p->step.y;
			p->side = 1;
		}
		if (map->map[p->map.x][p->map.y] == '1' || map->map[p->map.x][p->map.y] == 'D')
			p->hit = 1;
		if (map->map[p->map.x][p->map.y] == 'D')
			p->door = 1;
	}
}

void	draw_rayons_all_2(t_map *map, t_drawrays *r, t_plane *p, int i, int max)
{
	int	y;
	t_luno2f col;

	y = -1;
	r->step = 1.0 * 512 / r->lineh;
	r->texpos = (r->draw.x - HEIGHT_2 - p->drawstart + r->lineh / 2) * r->step ;
	while (++y < HEIGHT)
	{
		if (y < r->draw.x)// + p->drawstart)
			r->color = create_rgb(0, 0, max / 2, 255);
		else if (y > r->draw.y)// + p->drawend)
		{
			r->color = create_rgb(0, 0, 50, 35);
			col.y = max / 7;
			col.x = max / 5;
			if (col.x >= 50 && col.y >= 35)
				r->color = create_rgb(0, 0, col.x, col.y);
		}
		else
		{
			r->tex.y = (int)r->texpos & (512 - 1);
			r->texpos += r->step;
			wall_color(map->plane, &r->color, r->tex);
		}
		map->plane->buff[y][(int)i] = r->color;
		p->re_buf = 1;
	}
	p->tex_buff[i] = r->pwall;
	p->door = 0;
}

static
t_luno2i	get_drawss(int lineh, t_plane *p)
{
	t_luno2i	draw;

	draw.x = p->drawstart;
	draw.y = p->drawend;

	draw.x += -lineh / 2 + HEIGHT_2;
	if (draw.x < 0)
		draw.x = 0;
	draw.y += lineh / 2 + HEIGHT_2;
	if (draw.y >= HEIGHT)
		draw.y = HEIGHT - 1;
	return (draw);
}

void	draw_rayons_all(t_map *map, t_plane *p, int max, int time)
{
	t_drawrays	r;
	int			i;

	i = -1;
	if (p->re_buf == 1)
		ft_memset(&p->buff, 0, sizeof(int) * WIDTH * HEIGHT);
	while (++i < WIDTH)
	{
		init_cast(p, i);
		init_steps(p);
		dda(map, p);
		r.pwall = sides(map->plane);
		r.lineh = (int)(HEIGHT / r.pwall);
		r.draw = get_drawss(r.lineh, p);
		r.texnum = map->map[p->map.x][p->map.y] - '0' - 1;
		r.wallx = get_wall_x(p, r.pwall);
		r.tex.x = get_tex_x(p, r.wallx);
		draw_rayons_all_2(map, &r, p, i, max);
	}
	init_sprite(p, time, map->pos_q);
}
