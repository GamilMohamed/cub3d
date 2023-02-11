/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 04:03:03 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/11 04:11:09 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_map *map, int *texture, char *path, t_img *img)
{
	int	i;
	int	j;

	img->img = mlx_xpm_file_to_image(map->mlx->mlx, path, &img->w, &img->h);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l,
			&img->endian);
	i = -1;
	while (++i < img->h)
	{
		j = -1;
		while (++j < img->w)
			texture[img->w * i + j] = img->data[img->w * i + j];
	}
	mlx_destroy_image(map->mlx->mlx, img->img);
}

void	draw(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			map->img.data[WIDTH * i + j] = map->plane->buff[i][j];
	}
	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->img.img, 0, 0);
}

void	load_texture(t_map *map)
{
	t_img	img;

	load_image(map, map->plane->texture[0], map->path[0], &img);
	load_image(map, map->plane->texture[1], map->path[1], &img);
	load_image(map, map->plane->texture[2], map->path[2], &img);
	load_image(map, map->plane->texture[3], map->path[3], &img);
}
