/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 04:03:03 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/18 05:02:29 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	load_image(t_map *map, int *texture, char *path, t_image *img)
{
	int	i;
	int	j;

	img->img = mlx_xpm_file_to_image(map->mlx->mlx, path, &img->w, &img->h);
	if (!img->img)
		return (printf("%swrong texture path! %s\n", RED, RESET), 1);
	// if (img->w != 512 || img->h != 512){
		// printf("%i %i\n", img->w, img->h);
		// printf("path: %s\n", path);
		// return (printf("%simage si	ze must be 512x512! %s\n", RED, RESET), 1);
	// }
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
	int			i;
	int			j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			map->img.data[WIDTH * i + j] = map->plane->buff[i][j];
	}
	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->img.img, 0, 0);
}

void	fill_clock(char clock[64][1024])
{
	int	i;

	i = -1;
	while (++i < 64)
	{
		ft_strcpy(clock[i], "clock/clock_");
		ft_stoval(clock[i], i, 12, 12 + lenof(i));
		ft_strcat(clock[i], ".xpm");
	}
}

void	init_clock(t_plane *p)
{
	int	i;

	p->tex_clock = (int **)ft_calloc(sizeof(int), 64 * 64);
	i = -1;
	while (++i < 64)
		p->tex_clock[i] = (int *)ft_calloc(sizeof(int), (64 * 64));
}

int	load_clock(t_map *map, t_plane *p, t_image *img)
{
	int	j;
	int	r;
	int	i;

	i = -1;
	init_clock(map->plane);	
	while (++i < 64)
	{
		img->img = mlx_xpm_file_to_image(map->mlx->mlx, p->clock[i], &img->w,
				&img->h);
		if (!img->img)
			return (printf("%swrong texture path! %s\n", RED, RESET), 1);
		img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l,
				&img->endian);
		r = -1;
		while (++r < img->w)
		{
			j = -1;
			while (++j < img->h)
				p->tex_clock[i][img->w * r + j] = img->data[img->w * r + j];
		}
		mlx_destroy_image(map->mlx->mlx, img->img);
	}
	return (0);
}

void	load_texture(t_map *map)
{
	t_image	img;

	if (load_image(map, map->plane->texture[0], map->path[0], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[1], map->path[1], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[2], map->path[2], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[3], map->path[3], &img))
		mlx_loop_end(map->mlx->mlx);
	if (load_image(map, map->plane->texture[4], "wool/brown_wool.xpm", &img))
		mlx_loop_end(map->mlx->mlx);
	fill_clock(map->plane->clock);
	if (load_clock(map, map->plane, &img))
		mlx_loop_end(map->mlx->mlx);
}
