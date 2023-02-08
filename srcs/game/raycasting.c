/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:06:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/08 06:40:29 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	calc_rayons(t_temp *tmp, Luno2f coords, t_map *map)
// {
// 	Luno2f	jspr;
// 	double	l;

// 	l = (tmp->width + tmp->height) * cos((M_PI / 180));
// 	jspr.x = coords.x + cos((map->rotation) * (M_PI / 180)) * l;
// 	jspr.y = coords.y + sin((map->rotation) * (M_PI / 180)) * l;
// 	tmp->endray[0] = draw_line_rays(map, jspr, coords, 0xFF0000);
// 	jspr.x = coords.x + cos((map->rotation - 90) * (M_PI / 180)) * l;
// 	jspr.y = coords.y + sin((map->rotation - 90) * (M_PI / 180)) * l;
// 	tmp->endray[1] = draw_line_rays(map, jspr, coords, 0x00FF00);
// 	jspr.x = coords.x + cos((map->rotation + 90) * (M_PI / 180)) * l;
// 	jspr.y = coords.y + sin((map->rotation + 90) * (M_PI / 180)) * l;
// 	tmp->endray[2] = draw_line_rays(map, jspr, coords, 0x0000FF);
// }

void	verLine(t_temp *temp, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		my_mlx_pixel_put(temp, x, y, color);
		y++;
	}
}


void	init_cast(t_map *map, t_plane *plane, int index)
{
	plane->camera.x = 2 * index / (double)map->data->win_w - 1;
	plane->raydir = plane->dir + plane->plane * plane->camera.x;
	plane->map.x = (int)map->pos.x;
	plane->map.y = (int)map->pos.y;
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
		if (map->map[p->map.y][p->map.x] == '1')
			p->hit = 1;
	}
}

		// if (map->plane->side == 0)
		// 	pwall = map->plane->sdist.x - map->plane->deltadist.x;
		// else
		// 	pwall = map->plane->sdist.y - map->plane->deltadist.y;


void	draw_rayons_all(t_temp *tmp, Luno2f coords, t_map *map)
{
	Luno2f	jspr;
	double	l;
	double	ray;
	double	radius;
	int		width;
	int		height;
	int		color;
	double	pwall;
	int		lineh;
	int		drawstart;
	int		drawend;
	Luno2f	test;

	width = map->data->win_w;
	height = map->data->win_h;
	jspr = 0;
	ray = width / 2;
	color = 0xFFF354;
	for (double i = 0; i < width; i++)
	{
		init_cast(map, map->plane, i);
		init_steps(map, map->plane);
		dda(map, map->plane);
		if (map->plane->side == 0)
			pwall = (map->plane->map.x - map->plane->pos.x + (1 - map->plane->step.x) / 2) / map->plane->raydir.x;
		else
			pwall = (map->plane->map.y - map->plane->pos.y + (1 - map->plane->step.y) / 2) / map->plane->raydir.y;
		lineh = (int)(height / pwall);
		drawstart = -lineh / 2 + height / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineh / 2 + height / 2;
		if (drawend >= height)
			drawend = height - 1;
		if (map->plane->side == 1)
			color = 0x21FCaB;
		verLine(map->temp, i, 0, drawstart, create_trgb(map->ceiling));
		verLine(map->temp, i, drawstart, drawend, color);
		verLine(map->temp, i, drawend, height, create_trgb(map->floor));
		// if (i < width)
		// {
		// 	radius = calc_radius((i - (ray)) / (ray)*45.);
		// 	l = (50) * cos(radius);
		// 	radius = calc_radius((map->plane->dir.x - ((i - (ray)) / (ray)*45.)));
		// 	jspr.x = coords.x + cos(radius) * l;
		// 	jspr.y = coords.y + sin(radius) * l;
		// 	printf("coords.x %f | %f\n", coords.x, coords.y);
		// 	test = draw_line_rays(map, jspr, coords, 1);
		// }
	}
}

void	camera_rays(t_temp *tmp, t_map *map, Luno2f coords, double size)
{
	Luno2f	end;
	Luno2f	camera;
	double	rad;

	// draw_circle(tmp, map->plane->pos * 24, tmp->size / 4);
	// calc_rayons(tmp, map->plane->pos * 24 , map);
	draw_rayons_all(tmp, map->plane->pos * 24, map);
}
