/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:09:28 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/18 04:00:14 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	lenof(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = (n < 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	wall_color(t_plane *p, unsigned int *color, t_luno2i tex)
{
	if (p->side == 1)
	{
		if (p->raydir.y > 0)
			*color = p->texture[0][512 * tex.y + tex.x];
		else
			*color = p->texture[1][512 * tex.y + tex.x];
	}
	else
	{
		if (p->raydir.x > 0)
			*color = p->texture[3][512 * tex.y + tex.x];
		else
			*color = p->texture[2][512 * tex.y + tex.x];
	}
	if (p->door == 1)
		*color = p->texture[4][512 * tex.y + tex.x];
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

t_luno2i	get_draw(int lineh)
{
	t_luno2i	draw;

	draw.x = -lineh / 2 + HEIGHT_2;
	if (draw.x < 0)
		draw.x = 0;
	draw.y = lineh / 2 + HEIGHT_2;
	if (draw.y >= HEIGHT)
		draw.y = HEIGHT - 1;
	return (draw);
}

double	get_wall_x(t_plane *p, double pwall)
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

	val = (int)(wallx * (double)(512));
	if (p->side == 0 && p->raydir.x > 0)
		val = 512 - val - 1;
	if (p->side == 1 && p->raydir.y < 0)
		val = 512 - val - 1;
	return (val);
}
