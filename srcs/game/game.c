/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/06 16:51:18 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static
void	draw_line_rays_main(t_temp *temp, Luno2f end, Luno2f coords, bool print)
{
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

	double r = 0;
	int colorize = 0;

	dx = end.x - coords.x;
	dy = end.y - coords.y;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	incx = 1;
	if (end.x < coords.x)
		incx = -1;
	incy = 1;
	if (end.y < coords.y)
		incy = -1;
	x = (int)coords.x;
	y = (int)coords.y;
	if (dx > dy)
	{
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			my_mlx_pixel_put(temp, x, y, create_trgb((int [3]){255 - (int)r / 2, 255 - (int)r / 2, 255}));
			if (r < 255)
				r += 1;
		}
	}
	else
	{
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (e >= 0)
			{
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			my_mlx_pixel_put(temp, x, y, create_trgb((int [3]){255 - (int)r / 2, 255 - (int)r / 2, 255}));
			if (r < 255)
				r += 1;
		}
	}
	return ;
}


void	printcoords(Luno2i val, Luno2f val2)
{
	if (val.x)
		printf("val.x:%i, val.y:%i\n", val.x, val.y);
	if (val2.x)
		printf("val2.x:%f, val2.y:%f\n", val2.x, val2.y);
}

void	make_plane(t_map *map, t_temp *mini)
{
	Luno2f	jspr;
	double	l;

	l = (mini->width + mini->height) * cos((M_PI / 180));
	jspr.x = mini->coords.x + cos((map->rotation + 90) * (M_PI / 180)) * l;
	jspr.y = mini->coords.y + sin((map->rotation + 90) * (M_PI / 180)) * l;
	mini->plane[0] = draw_line_rays(map, jspr, mini->coords, 1);
	l = (mini->width + mini->height) * cos((M_PI / 180));
	jspr.x = mini->coords.x + cos((map->rotation - 90) * (M_PI / 180)) * l;
	jspr.y = mini->coords.y + sin((map->rotation - 90) * (M_PI / 180)) * l;
	mini->plane[1] = draw_line_rays(map, jspr, mini->coords, 1);
	pixel(mini, mini->plane[0], 0xFF0000);
	pixel(mini, mini->plane[1], 0x00FF00);
}

void	print_game(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{

}

void print_to_map(void *ptr)
{
	t_map *map;

	map = ptr;
	backgroundcolor(map, map->mlx, map->data, map->temp);
	fill_minimap(map, map->mlx, map->data);
	make_plane(map, map->mini);
	print_game(map, map->mlx, map->data, map->temp);
}

void	test(void *param)
{
	t_map *map = param;

	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx->mlx);
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_W))
		move_to_pos(map, normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_S))
		move_to_pos(map, -normalize(map->mini->endray[0] - map->mini->coords), map->mini->endray[0]);
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_A))
		move_to_pos(map, normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_D))
		move_to_pos(map, -normalize(map->mini->endray[1] - map->mini->coords), map->mini->endray[1]);
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_UP))
		map->nbrayons += 10;
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_DOWN))
		map->nbrayons -= 10;
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_RIGHT))
		map->rotation += 5;
	if (mlx_is_key_down(map->mlx->mlx, MLX_KEY_LEFT))
		map->rotation -= 5;
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	int r;

	map->temp = ft_calloc(sizeof(t_temp), 1);
	map->mini = ft_calloc(sizeof(t_temp), 1);
	map->plane = ft_calloc(sizeof(t_plane), 1);
	if (initmlx(map, mlx, data, map->temp))
		return (1);
	map->nbrayons = 2;
	init_minimap(map, mlx, data);
	mlx_image_to_window(mlx->mlx, map->temp->img, 0, 0);
	mlx_image_to_window(mlx->mlx, map->mini->img, 35, 35);
	mlx_loop_hook(mlx->mlx, print_to_map, (void *)map);
	mlx_loop_hook(mlx->mlx, test, (void *)map);
	mlx_loop(mlx->mlx);
	mlx_delete_image(mlx->mlx, map->temp->img);
	mlx_delete_image(mlx->mlx, map->mini->img);
	mlx_terminate(mlx->mlx);
	free(map->mini);
	free(map->temp);
	return (0);
}

/*

ETAPE 1: mini so long

ETAPE 2: tourner camera

ETAPE 3: ligne de 10pixel bien droit 

ETAPE 4: la ligne doit mtn sarreter au 1er mur

ETAPE 5: ligne x fov




*/