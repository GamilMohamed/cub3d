/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:41:29 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/16 22:20:01 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_pixel_put(t_help *help, unsigned int x, unsigned int y,
		unsigned int color)
{
	char	*dst;

	dst = (char *)help->addr + (y * help->size_l + x * (help->bpp / 8));
	*(unsigned int *)dst = color;
}

ssize_t	mlx_get_pixel(t_help *help, unsigned int x, unsigned int y)
{
	char	*src;

	help->addr = (int *)mlx_get_data_addr(help->img, &help->bpp, &help->size_l,
			&help->endian);
	if (!help->addr)
		return (-1);
	src = (char *)help->addr + (y * help->size_l + x * (help->bpp / 8));
	return (*(unsigned int *)src);
}

void	print_help(t_map *map, t_help *help)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	color;

	y = 0;
	while (y < (unsigned int)help->h)
	{
		x = 0;
		while (x < (unsigned int)help->w)
		{
			color = mlx_get_pixel(help, x, y);
			if (!(color == 0x00))
				map->plane->buff[HEIGHT_4 + y][WIDTH_4 + x] = color;
			x++;
		}
		y++;
	}
}
