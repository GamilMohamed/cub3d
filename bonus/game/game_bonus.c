/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/18 04:50:16 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_text(t_plane *plane)
{
	int	i;

	i = -1;
	while (++i < 5)
		free(plane->texture[i]);
	i = -1;
	while (++i < 512)
		free(plane->tex_clock[i]);
	free(plane->texture);
	free(plane->tex_clock);
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
	free(map->mini);
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

// static
// void	mouse_rotation(t_plane *p, int axis, double rot)
// {
// 	double	olddir;
// 	double	oldplane;

// 	olddir = p->dir.x;
// 	p->dir.x = p->dir.x * cos(rot) - p->dir.y * sin(rot);
// 	p->dir.y = olddir * sin(rot) + p->dir.y * cos(rot);
// 	oldplane = p->plane.x;
// 	p->plane.x = p->plane.x * cos(rot) - p->plane.y * sin(rot);
// 	p->plane.y = oldplane * sin(rot) + p->plane.y * cos(rot);
// }

/*//*/

int	near_door(t_map *map, char c)
{
	int	x;
	int	y;

	x = (int)map->plane->pos.x;
	y = (int)map->plane->pos.y;
	if (map->map[x][y] == c)
		return (0);
	if (map->map[x][y + 1] == c)
		return (1);
	else if (map->map[x][y - 1] == c)
		return (1);
	else if (map->map[x + 1][y] == c)
		return (1);
	else if (map->map[x - 1][y] == c)
		return (1);
	return (0);
}

int		mouse_press(int button, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	map->press->door = 0;
	if (button == 3 && near_door(map, 'C')) // && map->press->door != 1)
		map->press->door = 1;
	if (button == 3 && near_door(map, 'D'))// && map->press->door != 2)
		map->press->door = 2;
	printf("in mouse door = %d\n", map->press->door);
	if (button == 1 && map->press->m != 2)
		map->press->m = 2;
	else if (button == 1 && map->press->m != 1)
		map->press->m = 1;
	return (0);
}

int	ft_mouse_move(t_map *map)
{
	char	p;
	int		ret;
	int x, y;
	p = map->data->player;
	ret = 0;
	mlx_mouse_get_pos(map->mlx->mlx, map->mlx->win, &x, &y);
	// mlx_get(map->mlx->mlx, &x, &y);
	if (p == 'N' || p == 'S')
		ret = 1;
	if (y >= HEIGHT)
		mlx_mouse_move(map->mlx->mlx, map->mlx->win, WIDTH_2, HEIGHT);

	if (x > WIDTH_2 - 5 || x < WIDTH_2 + 5)
	{
		if (x >= WIDTH_2)
			mouse_rotation(map->plane, (ret == 0), (x - WIDTH_2) * 0.005);
		else
			mouse_rotation(map->plane, (ret != 0), (WIDTH_2 - x) * 0.005);
	}
	if (y > HEIGHT_2 - 5 || y < HEIGHT_2 + 5)
	{
		if (y >= HEIGHT_2)
		{
			map->plane->drawstart = (y - HEIGHT_2) * -1;
			map->plane->drawend = (y - HEIGHT_2) * -1;
		}
		else
		{
			map->plane->drawstart = (HEIGHT_2 - y) * 1;
			map->plane->drawend = (HEIGHT_2 - y) * 1;
		}
	}
	// if (x != WIDTH_2 && y != HEIGHT_2)
	mlx_mouse_move(map->mlx->mlx, map->mlx->win, WIDTH_2, y);
	return (0);
}



// int	mouse_move(int x, int y, t_map *map)
// {
// 	char	p;
// 	int		ret;

// 	p = map->data->player;
// 	ret = 0;
// 	mlx_get_screen_size(map->mlx->mlx, &x, &y);
// 	if (p == 'N' || p == 'S')
// 		ret = 1;
// 	if (x > WIDTH_2 - 5 || x < WIDTH_2 + 5)
// 	{
// 		if (x >= WIDTH_2)
// 			mouse_rotation(map->plane, (ret == 0), (x - WIDTH_2) * 0.005);
// 		else
// 			mouse_rotation(map->plane, (ret != 0), (WIDTH_2 - x) * 0.005);
// 	}
// 	if (y > HEIGHT_2 - 5 || y < HEIGHT_2 + 5)
// 	{
// 		if (y >= HEIGHT_2)
// 		{
// 			map->plane->drawstart = (y - HEIGHT_2) * -1;
// 			map->plane->drawend = (y - HEIGHT_2) * -1;
// 		}
// 		else
// 		{
// 			map->plane->drawstart = (HEIGHT_2 - y) * 1;
// 			map->plane->drawend = (HEIGHT_2 - y) * 1;
// 		}
// 	}
// 	// if (x != WIDTH_2 && y != HEIGHT_2)
// 		mlx_mouse_move(map->mlx->mlx, map->mlx->win, WIDTH_2, y);
// 	return (0);
// }


int	initminimap(t_map *map, t_temp *mini)
{
	(void)map;
	mini->size = 15;
	printf("mini->size = %f\n", mini->size);
	printf("map->maxlen = %d\n", map->maxlen);
	printf("map->height = %d\n", map->height);
	return (0);
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	(void)data;
	t_xvar *louis;
	t_win_list *window;
	
	map->temp = ft_calloc(sizeof(t_temp), 1);
	map->plane = ft_calloc(sizeof(t_plane), 1);
	map->press = ft_calloc(sizeof(t_press), 1);
	map->mini = ft_calloc(sizeof(t_temp), 1);
	if (initmlx(map, mlx))
		return (1);
	louis = (t_xvar *)mlx->mlx;
	if (initminimap(map, map->mini))
		return (1);
	map->data->player_pos = map->pos;
	map->data->player_pos = map->pos;
	map->plane->drawstart = 0;
	map->press->door = 0;
	map->mini->front = map->pos;
	map->help.img = mlx_xpm_file_to_image(map->mlx->mlx, "s/help.xpm",
			&map->help.w, &map->help.h);
	map->help.addr = (int *)mlx_get_data_addr(map->help.img, &map->help.bpp,
			&map->help.size_l, &map->help.endian);
	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->help.img, 0, 0);
	init_plane(map->plane, map);
	init_buff(map->plane);
	load_texture(map);
	window = (t_win_list *)mlx->win;
	XFixesHideCursor(louis->display, window->window);
	mlx_hook(mlx->win, 2, 1L << 0, &key_press, map);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_press, map);
	mlx_hook(mlx->win, 3, 1L << 1, &key_release, map);
	mlx_hook(mlx->win, 17, 0, &ft_close, map);
	mlx_loop_hook(mlx->mlx, &move, map);
	mlx_loop(mlx->mlx);
	mlx_mouse_show(mlx->mlx, mlx->win);
	destroywindows(mlx, map);
	return (0);
}
