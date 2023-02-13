/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/13 07:44:31 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_text(t_plane *plane)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(plane->texture[i]);
	free(plane->texture);
}

void	destroywindows(t_mlx *mlx, t_map *map)
{
	mlx_destroy_image(mlx->mlx, map->img.img);
	mlx_destroy_image(mlx->mlx, map->help.img);
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_text(map->plane);
	free(mlx->mlx);
	free(map->plane);
	free(map->press);
	free(map->temp);
}

int	ft_close(t_map *map)
{
	mlx_loop_end(map->mlx->mlx);
	return (1);
}

static void	mouse_rotation(t_plane *p, int axis, double rot)
{
	double	olddir;
	double	oldplane;

	if (axis)
		rot = -rot;
	olddir = p->dir.x;
	p->dir.x = p->dir.x * cos(rot) - p->dir.y * sin(rot);
	p->dir.y = olddir * sin(rot) + p->dir.y * cos(rot);
	oldplane = p->plane.x;
	p->plane.x = p->plane.x * cos(rot) - p->plane.y * sin(rot);
	p->plane.y = oldplane * sin(rot) + p->plane.y * cos(rot);
}

int	mouse_press(int button, int x, int y, t_map *map)
{
	static int	r;

	if (r++ % 2)
		map->press->m = 1;
	else
		map->press->m = 2;
	return (0);
}

int	mouse_move(int x, int y, t_map *map)
{
	char	p;
	int		middle_x;
	int		middle_y;
	int		ret;

	p = map->data->player;
	middle_x = WIDTH / 2;
	middle_y = HEIGHT / 2;
	ret = 0;
	if (p == 'N' || p == 'S')
		ret = 1;
	if (x != middle_x)
	{
		if (x >= middle_x)
			mouse_rotation(map->plane, (ret == 0), (x - middle_x) * 0.005);
		else
			mouse_rotation(map->plane, (ret != 0), (middle_x - x) * 0.005);
	}
	mlx_mouse_move(map->mlx->mlx, map->mlx->win, middle_x, middle_y);
	return (0);
}

int	initminimap(t_map *map, t_temp *mini)
{
	int	r;

	mini->size = 15;
	mini->width = map->maxlen * mini->size;
	mini->height = map->height * mini->size;
	mini->img = mlx_new_image(map->mlx->mlx, mini->width, mini->height);
	mini->addr = mlx_get_data_addr(mini->img, &mini->a, &mini->b, &mini->c);
	return (0);
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	int	r;

	(void)data;
	map->temp = ft_calloc(sizeof(t_temp), 1);
	map->plane = ft_calloc(sizeof(t_plane), 1);
	map->press = ft_calloc(sizeof(t_press), 1);
	map->mini = ft_calloc(sizeof(t_temp), 1);
	if (initmlx(map, mlx))
		return (1);
	if (initminimap(map, map->mini))
		return (1);
	map->help.img = mlx_xpm_file_to_image(map->mlx->mlx, "s/help.xpm", &r, &r);
	mlx_mouse_hide(mlx->mlx, mlx->win);
	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->help.img, 0, 0);
	init_plane(map->plane, map);
	init_buff(map->plane);
	load_texture(map);
	mlx_hook(mlx->win, 2, 1L << 0, &key_press, map);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_press, map);
	mlx_hook(mlx->win, MotionNotify, PointerMotionMask, mouse_move, map);
	// mlx_hook(mlx->win, 5, 1L << 4, &mouse_move, map);
	mlx_hook(mlx->win, 3, 1L << 1, &key_release, map);
	mlx_hook(mlx->win, 17, 0, &ft_close, map);
	mlx_loop_hook(mlx->mlx, &move, map);
	mlx_loop(mlx->mlx);
	destroywindows(mlx, map);
	return (0);
}
