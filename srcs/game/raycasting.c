/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:06:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/06 16:51:46 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_rayons(t_temp *tmp, Luno2f coords, t_map *map)
{
	Luno2f	jspr;
	double	l;

	l = (tmp->width + tmp->height) * cos((M_PI / 180));
	jspr.x = coords.x + cos((map->rotation) * (M_PI / 180)) * l;
	jspr.y = coords.y + sin((map->rotation) * (M_PI / 180)) * l;
	tmp->endray[0] = draw_line_rays(map, jspr, coords, 1);
	l = (tmp->width + tmp->height) * cos((M_PI / 180));
	jspr.x = coords.x + cos((map->rotation - 90) * (M_PI / 180)) * l;
	jspr.y = coords.y + sin((map->rotation - 90) * (M_PI / 180)) * l;
	tmp->endray[1] = draw_line_rays(map, jspr, coords, 0);
	// pixel(tmp, tmp->endray[0], 0xFF0000);
	// pixel(tmp, tmp->endray[1], 0x00FF00);
}

// void	draw_rayons_all(t_temp *tmp, Luno2f coords, t_map *map)
// {
// 	Luno2f jspr = 0;
// 	double	l;
// 	double ray;

// 	ray = map->nbrayons / 2;
// 	// calc_radius()
// 	for (double i = 1; i < map->nbrayons; i++)
// 	{
// 		l = (tmp->width + tmp->height) * cos(((i - (ray)) / (ray) * 45.) * (M_PI
					// / 180));
		// jspr.x = coords.x + cos((map->rotation - ((i - (ray)) / (ray) * 45.))
				// * (M_PI / 180)) * l;
// 		jspr.y = coords.y + sin((map->rotation - ((i - (ray)) / (ray) * 45.))
				// * (M_PI / 180)) * l;
// 		draw_line_rays(map, jspr, coords, ((i - (ray)) / (ray) * 45.));
// 	}
// }

void	verLine(void *addr, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_put_pixel(addr, x, y, color);
		y++;
	}
}

void	walldrawing(t_map *map, Luno2f test, Luno2f coords)
{
	int cube = 35;
	int	VRES = map->data->win_h;
	double wall;

	double dist = sqrt(pow(test.x - coords.x, 2) + pow(test.y - coords.y, 2));
	if (dist > VRES)
		dist = VRES;
	wall = cube * VRES / dist;
	double offset = VRES - wall;
	verLine(map->temp->img, 50, 100, 100, 0xFAC120F);
	// verLine(map->temp->img, coords.x, test.y, test.x, 0xFAC120F);
	// verLine(map->temp->img, 0, offset, cube, 0xFAC120F);
	// printf("wall:%f, offset:%f\n", wall, offset);
}

void	draw_rayons_all(t_temp *tmp, Luno2f coords, t_map *map)
{
	Luno2f	jspr;
	double	l;
	double	ray;
	double	radius;

	jspr = 0;
	
	ray = map->nbrayons / 2;
	// printf("ray=%f\n", ray);
	map->plane->pos = map->data->player_pos;
	map->plane->dir.x = -1;
	map->plane->dir.y = 0;
	map->plane->plane.x = 0;
	map->plane->plane.y = 0.66;
	map->plane->moveSpeed = 0.05;
	map->plane->rotSpeed = 0.05;
	for (double i = 0; i < map->nbrayons; i++)
	{
		radius = calc_radius((i - (ray)) / (ray)*45.);
		l = (tmp->width * tmp->height) * cos(radius);
		radius = calc_radius((map->rotation - ((i - (ray)) / (ray)*45.)));
		jspr.x = coords.x + cos(radius) * l;
		jspr.y = coords.y + sin(radius) * l;
		Luno2f test = draw_line_rays(map, jspr, coords, 1);
		// walldrawing(map, test, coords);
		// p->_plane(tmp, map, test, coords, map->plane, i);
	}
}

void	camera_rays(t_temp *tmp, t_map *map, Luno2f coords, double size)
{
	Luno2f	end;
	double	rad;

	draw_circle(tmp, tmp->coords, tmp->size / 4);
	rad = calc_radius(map->rotation - 90.);
	end = calc_rotation(tmp->coords, tmp->size, rad, 1);
	// draw_line_rays(map, end, tmp->coords, 0xF2BFA3);
	rad = calc_radius(map->rotation + 90.);
	end = calc_rotation(tmp->coords, tmp->size, rad, 1);
	// draw_line_rays(map, end, tmp->coords, 0xF2BFA3);
	calc_rayons(tmp, coords, map);
	draw_rayons_all(tmp, coords, map);
}
