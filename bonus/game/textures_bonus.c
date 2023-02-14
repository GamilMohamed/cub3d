/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 04:03:03 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/14 10:34:00 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	load_image(t_map *map, int *texture, char *path, t_img *img)
{
	int	i;
	int	j;

	img->img = mlx_xpm_file_to_image(map->mlx->mlx, path, &img->w, &img->h);
	if (!img->img)
	{
		printf("%s\n", path);
		return (printf("%swrong texture path! %s\n", RED, RESET), 1);
	}
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
	return (0);
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

	if (load_image(map, map->plane->texture[0], map->path[0], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[1], map->path[1], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[2], map->path[2], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[3], map->path[3], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[4], "s/W.xpm", &img))
		mlx_loop_end(map->mlx->mlx);
}
