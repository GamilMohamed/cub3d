/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:06:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/06 08:32:07 by mgamil           ###   ########.fr       */
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
	pixel(tmp, tmp->endray[0], 0xFF0000);
	pixel(tmp, tmp->endray[1], 0x00FF00);
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

void	draw_rayons_all(t_temp *tmp, Luno2f coords, t_map *map)
{
	Luno2f	jspr;
	double	l;
	double	ray;
	double	radius;

	jspr = 0;
	ray = map->nbrayons / 2;
	for (double i = 1; i < map->nbrayons; i++)
	{
		radius = calc_radius((i - (ray)) / (ray)*45.);
		l = (tmp->width + tmp->height) * cos(radius);
		radius = calc_radius((map->rotation - ((i - (ray)) / (ray)*45.)));
		jspr.x = coords.x + cos(radius) * l;
		jspr.y = coords.y + sin(radius) * l;
		draw_line_rays(map, jspr, coords, ((i - (ray)) / (ray)*45.));
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
