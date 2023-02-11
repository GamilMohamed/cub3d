/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 07:59:49 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/11 04:14:59 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

Luno2i	convert_d_to_i(Luno2f src)
{
	Luno2i	ret;

	ret.x = (int)src.x;
	ret.y = (int)src.y;
	return (ret);
}

Luno2f	calc_rotation(Luno2f coords, int r, double rad, int m)
{
	return ((Luno2f){coords.x + r * m * cos(rad), coords.y + r * sin(rad)});
}

double	calc_radius(double angle)
{
	return (angle * (M_PI / 180));
}

Luno2f	normalize(Luno2f coords)
{
	double	size;

	size = sqrtf(pow(coords.x, 2) + pow(coords.y, 2));
	coords /= size;
	return (coords);
}
