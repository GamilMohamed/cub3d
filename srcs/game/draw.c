/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:03:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/09 19:09:56 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_temp *temp, int x, int y, int color)
{
	char	*dst;

	dst = temp->addr + (y * temp->b + x * (temp->a / 8));
	*(unsigned int*)dst = color;
}

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
