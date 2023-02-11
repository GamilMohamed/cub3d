/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:06:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/11 05:45:13 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cast(t_map *map, t_plane *plane, int index)
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

void	init_steps(t_map *map, t_plane *p)
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
		if (map->map[p->map.x][p->map.y] == '1')
			p->hit = 1;
	}
}

void	wall_color(t_map *map, t_plane *p, int *color, Luno2i tex)
{
	if (p->side == 1)
	{
		if (p->raydir.y > 0)
			*color = p->texture[0][64 * tex.y + tex.x];
		else
			*color = p->texture[1][64 * tex.y + tex.x];
	}
	else
	{
		if (p->raydir.x > 0)
			*color = p->texture[3][64 * tex.y + tex.x];
		else
			*color = p->texture[2][64 * tex.y + tex.x];
	}
}

double	sides(t_plane *p)
{
	double	pwall;

	if (p->side == 0)
		pwall = (p->map.x - p->pos.x + (1 - p->step.x) / 2) / p->raydir.x;
	else
		pwall = (p->map.y - p->pos.y + (1 - p->step.y) / 2) / p->raydir.y;
	return (pwall);
}

Luno2i	get_draw(int lineh)
{
	Luno2i	draw;

	draw.x = -lineh / 2 + HEIGHT / 2;
	if (draw.x < 0)
		draw.x = 0;
	draw.y = lineh / 2 + HEIGHT / 2;
	if (draw.y >= HEIGHT)
		draw.y = HEIGHT - 1;
	return (draw);
}

double	get_wall_x(t_map *map, t_plane *p, double pwall)
{
	double	wallx;

	if (p->side == 0)
		wallx = p->pos.y + pwall * p->raydir.y;
	else
		wallx = p->pos.x + pwall * p->raydir.x;
	wallx -= floor(wallx);
	return (wallx);
}

int	get_tex_x(t_plane *p, double wallx)
{
	int	val;

	val = (int)(wallx * (double)(64));
	if (p->side == 0 && p->raydir.x > 0)
		val = 64 - val - 1;
	if (p->side == 1 && p->raydir.y < 0)
		val = 64 - val - 1;
	return (val);
}

void	draw_rayons_all_2(t_map *map, t_drawrays *r, t_plane *p, int i)
{
	int	y;

	y = -1;
	r->step = 1.0 * 64 / r->lineh;
	r->texPos = (r->draw.x - HEIGHT / 2 + r->lineh / 2) * r->step;
	while (++y < HEIGHT)
	{
		if (y < r->draw.x)
			r->color = create_trgb(map->ceiling);
		else if (y > r->draw.y)
			r->color = create_trgb(map->floor);
		else
		{
			r->tex.y = (int)r->texPos & (64 - 1);
			r->color = map->plane->texture[r->texnum][64 * r->tex.y + r->tex.x];
			r->texPos += r->step;
			wall_color(map, map->plane, &r->color, r->tex);
		}
		map->plane->buff[y][(int)i] = r->color;
		p->re_buf = 1;
	}
}

void	draw_rayons_all(t_map *map, t_temp *tmp, t_plane *p)
{
	t_drawrays	r;
	int			y;

	if (p->re_buf == 1)
		ft_memset(&p->buff, 0, sizeof(int) * WIDTH * HEIGHT);
	for (double i = 0; i < WIDTH; i++)
	{
		init_cast(map, p, i);
		init_steps(map, p);
		dda(map, p);
		r.pwall = sides(map->plane);
		r.lineh = (int)(HEIGHT / r.pwall);
		r.draw = get_draw(r.lineh);
		r.texnum = map->map[p->map.x][p->map.y] - '0' - 1;
		r.wallx = get_wall_x(map, p, r.pwall);
		r.tex.x = get_tex_x(p, r.wallx);
		draw_rayons_all_2(map, &r, p, i);
	}
}
