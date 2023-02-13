/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 07:59:49 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/12 20:49:20 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_luno2i	convert_d_to_i(t_luno2f src)
{
	t_luno2i	ret;

	ret.x = (int)src.x;
	ret.y = (int)src.y;
	return (ret);
}

t_luno2f	calc_rotation(t_luno2f coords, int r, double rad, int m)
{
	return ((t_luno2f){coords.x + r * m * cos(rad), coords.y + r * sin(rad)});
}

double	calc_radius(double angle)
{
	return (angle * (M_PI / 180));
}

t_luno2f	normalize(t_luno2f coords)
{
	double	size;

	size = sqrtf(pow(coords.x, 2) + pow(coords.y, 2));
	coords /= size;
	return (coords);
}
