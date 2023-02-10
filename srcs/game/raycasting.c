/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:06:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/10 20:40:59 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cast(t_map *map, t_plane *plane, int index)
{
	plane->camera.x = 2 * index / (double)map->data->win_w - 1;
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

void	wall_color_ns(t_map *map, t_plane *p, int *color, Luno2i tex)
{
	if (p->map.x + (1 - p->step.x) / 2 > p->pos.x)
	{
		*color = 0xFFFFFF;
		// *color = p->texture[3][64 * tex.y + tex.x];
	}
	else
	{
		*color = 0x000000;
		// *color = p->texture[2][64 * tex.y + tex.x];
	}
	*color = 0xFF0000;
	*color = (*color >> 1) & 8355711;
}

void	wall_color_ew(t_map *map, t_plane *p, int *color, Luno2i tex)
{
	if (p->side == 1)
	{
		if (p->map.x + (1 - p->step.x) / 2 > p->pos.x)
		{
			*color = 0xFF0000;
			// *color = p->texture[0][64 * tex.y + tex.x];
		}
		else
		{
			*color = 0x0000FF;
			// *color = p->texture[1][64 * tex.y + tex.x];
		}
		*color = 0x0000FF;
		*color = (*color >> 1) & 8355711;
	}
	else
		wall_color_ns(map, p, color, tex);
}


void	draw_rayons_all(t_map *map, t_temp *tmp, t_plane *p)
{
	int		width;
	int		height;
	double	pwall;
	int		lineh;
	int		texnum;
	Luno2i 	tex;
	Luno2i	draw;
	double	step;
	double	texPos;
	int	color;

	int texWidth = 64;  // width of texture
	int texHeight = 64; // height of texture
	width = map->data->win_w;
	height = map->data->win_h;
	int y;
	// color = 0xFFF354;
	if (p->re_buf == 1)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				p->buff[i][j] = 0;
			}
		}
	}
	for (double i = 0; i < width; i++)
	{
		init_cast(map, p, i);
		init_steps(map, p);
		dda(map, p);
		if (p->side == 0)
			pwall = (p->map.x - p->pos.x + (1 - p->step.x) / 2) / p->raydir.x;
		else
			pwall = (p->map.y - p->pos.y + (1 - p->step.y) / 2) / p->raydir.y;
		lineh = (int)(height / pwall);
		draw.x = -lineh / 2 + height / 2;
		if (draw.x < 0)
			draw.x = 0;
		draw.y = lineh / 2 + height / 2;
		if (draw.y >= height)
			draw.y = height - 1;
		// if (p->side == 1)
		// 	color = 0x21FCaB;
		/*                                  */
		texnum = map->map[p->map.x][p->map.y] - '0' - 1;

		double wallX; //where exactly the wall was hit
		if (p->side == 0)
			wallX = p->pos.y + pwall * p->raydir.y;
		else
			wallX = p->pos.x + pwall * p->raydir.x;
		wallX -= floor((wallX));
		printf("wallX = %f\n", wallX);
		tex.x = (int)(wallX * (double)(texWidth));
		if (p->side == 0 && p->raydir.x > 0)
			tex.x = texWidth - tex.x - 1;
		if (p->side == 1 && p->raydir.y < 0)
			tex.x = texWidth - tex.x - 1;
		double step = 1.0 * texHeight / lineh;
		texPos = (draw.x - height / 2 + lineh / 2) * step;
		// for (y = draw.x; y < draw.y; y++)
		//-0.59 180
		//-0.28 360
		//0.98  270
		//-0.44 90
		for (y = 0; y < height; y++)
		{
			if (y < draw.x)
				color = create_trgb(map->ceiling);
			else if (y > draw.y)
				color = create_trgb(map->floor);
			else
			{
				tex.y = (int)texPos & (texHeight - 1);
				// color = map->plane->texture[texnum][texHeight * tex.y + tex.x];
				// texPos += step;
				// if (p->side == 0) {
					// color = 0xFF0000;
					/*if (p->raydir.y < 0)
						color = 0x000000;
					if (p->raydir.y >= 0)
						color = 0xFFFFFF;*/
				// }
				// else {
				// 	color = 0x0000FF;
				// 	if (p->raydir.x < 0)
				// 		color = 0xFFFFFF;
				// 	if (p->raydir.x >= 0)
				// 		color = 0x0000FF;
				// }
				// printf("raydir.x:%f, raydfr.y:%f\n", p->raydir.x, p->raydir.y);
				//if (p->side == 1)
					//color = color / 2;
				// wall_color_ns(map, map->plane, &color, tex);
				wall_color_ew(map, map->plane, &color, tex);
			}
			map->plane->buff[y][(int)i] = color;
			p->re_buf = 1;
		}
		// printf("y = %i\n", y);
		// verLine(map->img.img, i, draw.x, draw.y, color);
		// verLine(map->img.img, i, draw.y, height, create_rgb(0, 121, 59, 12));
		// verLine(map->img.img, i, 0, draw.x, create_rgb(0, 124, 21, 255));
		// draw(map);
	}
}
