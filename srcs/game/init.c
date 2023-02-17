/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:01:09 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/17 23:35:26 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	orientation(t_plane *plane, char player)
{
	if (player == 'N')
	{
		plane->dir.x = 0;
		plane->dir.y = 1;
	}
	else if (player == 'S')
	{
		plane->dir.x = 0;
		plane->dir.y = -1;
	}
	else if (player == 'E')
	{
		plane->dir.x = 1;
		plane->dir.y = 0;
	}
	else if (player == 'W')
	{
		plane->dir.x = -1;
		plane->dir.y = 0;
	}
}

int	initmlx(t_map *map, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "cub3D");
	if (!mlx->win)
		return (ft_free((void **)&mlx->mlx), 1);
	map->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!map->img.img)
		return (1);
	map->img.data = (int *)mlx_get_data_addr(map->img.img, &map->img.bpp,
			&map->img.size_l, &map->img.endian);
	return (0);
}

void	init_buff(t_plane *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			p->buff[i][j] = 0;
	}
	p->texture = (int **)malloc(sizeof(int *) * (4 * 4));
	i = -1;
	while (++i < 4)
	{
		j = -1;
		p->texture[i] = (int *)malloc(sizeof(int) * (64 * 64));
		while (++j < (64 * 64))
			p->texture[i][j] = 0;
	}
}

void	init_plane(t_plane *plane, t_map *map)
{
	orientation(plane, map->data->player);
	plane->plane.x = 0.66 * (plane->dir.y);
	plane->plane.y = 0.66 * (-1 * plane->dir.x);
	plane->movespeed = 0.09;
	plane->rotspeed = 0.09;
	plane->pos = map->pos;
	plane->re_buf = 0;
}
