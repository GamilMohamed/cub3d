/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:20:48 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/02 00:37:53 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// // #include "cub3d.h"
// #include <math.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #define X_EVENT_KEY_PRESS	2
// #define X_EVENT_KEY_EXIT	17
// #define mapWidth 24
// #define mapHeight 24
// #define width 1920
// #define height 1080

// # define K_W 119
// # define K_A  97
// # define K_S  115
// # define K_D  100

// // # define K_A 0
// # define K_B 11
// # define K_C 8
// // # define K_D 2
// # define K_E 14
// # define K_F 3
// # define K_G 5
// # define K_H 4
// # define K_I 34
// # define K_J 38
// # define K_K 40
// # define K_L 37
// # define K_M 46
// # define K_N 45
// # define K_O 31
// # define K_P 35
// # define K_Q 12
// # define K_R 15
// // # define K_S 1
// # define K_T 17
// # define K_U 32
// # define K_V 9
// // # define K_W 13
// # define K_X 7
// # define K_Y 16
// # define K_Z 6

// /*
// ** Keyboard ARROWS
// */

// # define K_AR_L 123
// # define K_AR_R 124
// # define K_AR_U 126
// # define K_AR_D 125

// /*
// ** Keyboard NUMPAD
// */

// # define K_NP_DIV 75
// # define K_NP_MUL 67
// # define K_NP_MIN 78
// # define K_NP_PLU 69
// # define K_NP_1	83
// # define K_NP_2	84
// # define K_NP_3	85
// # define K_NP_4	86
// # define K_NP_5	87
// # define K_NP_6	88
// # define K_NP_7	89
// # define K_NP_8	91
// # define K_NP_9	92

// /*
// ** Keyboard MISC
// */

// # define K_SP 49
// # define K_ESC 53
// # define K_TAB 48

// /*
// ** Mouse
// */

// # define M_CLK_L 1
// # define M_CLK_R 3
// # define M_CLK_M 2
// # define M_SCR_U 4
// # define M_SCR_D 5

// typedef struct	s_info
// {
// 	double posX;
// 	double posY;
// 	double dirX;
// 	double dirY;
// 	double planeX;
// 	double planeY;
// 	void	*mlx;
// 	void	*win;
// 	double	moveSpeed;
// 	double	rotSpeed;
// }				t_info;

// int	worldMap[24][24] = {
// 							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 							{1,0,0,0,0,0,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,4,0,4,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,4,0,0,4,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,4,0,4,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 						};

// void	verLine(t_info *info, int x, int y1, int y2, int color)
// {
// 	int	y;

// 	y = y1;
// 	while (y <= y2)
// 	{
// 		mlx_pixel_put(info->mlx, info->win, x, y, color);
// 		y++;
// 	}
// }

// int	create_xtrgb(int a, int b, int c )
// {
// 	return (0 << 24 | a << 16 | b << 8 | c);
// }

// void	calc(t_info *info)
// {
// 	int	x;

// 	x = 0;
// 	while (x < width)
// 	{
// 		double cameraX = 2 * x / (double)width - 1;
// 		double rayDirX = info->dirX + info->planeX * cameraX;
// 		double rayDirY = info->dirY + info->planeY * cameraX;
// 		printf("%f|%f|%f\n", cameraX, rayDirX, rayDirY);

// 		int mapX = (int)info->posX;
// 		int mapY = (int)info->posY;

// 		//length of ray from current position to next x or y-side
// 		double sideDistX;
// 		double sideDistY;

// 			//length of ray from one x or y-side to next x or y-side
// 		double deltaDistX = fabs(1 / rayDirX);
// 		double deltaDistY = fabs(1 / rayDirY);
// 		printf("deltaDistX:%f, deltaDisty:%f\n", deltaDistX, deltaDistY);
// 		double perpWallDist;

// 		//what direction to step in x or y-direction (either +1 or -1)
// 		int stepX;
// 		int stepY;

// 		int hit = 0; //was there a wall hit?
// 		int side; //was a NS or a EW wall hit?

// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (info->posX - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (info->posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
// 		}

// 		while (hit == 0)
// 		{
// 			//jump to next map square, OR in x-direction, OR in y-direction
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			//Check if ray has hit a wall
// 			if (worldMap[mapX][mapY] > 0) hit = 1;
// 		}
// 		if (side == 0) // se
// 			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
// 		else // ns
// 			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
// 		printf("perpWallDist=%f\n", perpWallDist);
// 		//Calculate height of line to draw on screen
// 		int lineHeight = (int)(height / perpWallDist);
// 		//calculate lowest and highest pixel to fill in current stripe
// 		int drawStart = -lineHeight / 2 + height / 2;
// 		if(drawStart < 0)
// 			drawStart = 0;
// 		int drawEnd = lineHeight / 2 + height / 2;
// 		if(drawEnd >= height)
// 			drawEnd = height - 1;

// 		int	color;
// 		if (worldMap[mapY][mapX] == 1)
// 			color = 0xFF0000;
// 		else if (worldMap[mapY][mapX] == 2)
// 			color = 0x00FF00;
// 		else if (worldMap[mapY][mapX] == 3)
// 			color = 0x0000FF;
// 		else if (worldMap[mapY][mapX] == 4)
// 			color = 0xFFFFFF;
// 		else
// 			color = 0xFFFF00;

// 		if (side == 1)
// 			color = color / 2;

// 		verLine(info, x, drawStart, drawEnd, color);
// 		verLine(info, x, drawEnd, height, create_xtrgb(170,191,209));
// 		verLine(info, x, 0, drawStart, create_xtrgb(42,98,61));
// 		for (size_t i = 0; i < drawStart; i++)
// 		{

// 		}

// 		x++;
// 	}
// }

// int	main_loop(t_info *info)
// {
// 	calc(info);
// 	// mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);

// 	return (0);
// }

// int	key_press(int key, t_info *info)
// {
// 	if (key == K_W)
// 	{
// 		if (!worldMap[(int)(info->posX + info->dirX
// 					* info->moveSpeed)][(int)(info->posY)])
// 			info->posX += info->dirX * info->moveSpeed;
// 		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY
// 					* info->moveSpeed)])
// 			info->posY += info->dirY * info->moveSpeed;
// 	}
// 	//move backwards if no wall behind you
// 	if (key == K_S)
// 	{
// 		if (!worldMap[(int)(info->posX - info->dirX
// 					* info->moveSpeed)][(int)(info->posY)])
// 			info->posX -= info->dirX * info->moveSpeed;
// 		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY
// 					* info->moveSpeed)])
// 			info->posY -= info->dirY * info->moveSpeed;
// 	}
// 	//rotate to the right
// 	if (key == K_D)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = info->dirX;
// 		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY
// 			* sin(-info->rotSpeed);
// 		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY
// 			* cos(-info->rotSpeed);
// 		double oldPlaneX = info->planeX;
// 		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY
// 			* sin(-info->rotSpeed);
// 		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY
// 			* cos(-info->rotSpeed);
// 	}
// 	//rotate to the left
// 	if (key == K_A)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = info->dirX;
// 		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY
// 			* sin(info->rotSpeed);
// 		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY
// 			* cos(info->rotSpeed);
// 		double oldPlaneX = info->planeX;
// 		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY
// 			* sin(info->rotSpeed);
// 		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY
// 			* cos(info->rotSpeed);
// 	}
// 	if (key == K_ESC)
// 		exit(0);
// 	return (0);
// // }

// int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
// {
// 	t_info info;
// 	info.mlx = mlx_init();

// 	info.posX = 12;
// 	info.posY = 5;
// 	info.dirX = -1;
// 	info.dirY = 0;
// 	info.planeX = 0;
// 	info.planeY = 0.66;
// 	info.moveSpeed = 0.20;
// 	info.rotSpeed = 0.20;

// 	info.win = mlx_new_window(info.mlx, width, height, "mlx");

// 	mlx_loop_hook(info.mlx, &main_loop, &info);
// 	mlx_key_hook(info.win, &key_press, &info);

// 	mlx_loop(info.mlx);
// }

void	my_mlx_pixel_put(t_temp *temp, int x, int y, int color)
{
	char	*dst;

	dst = temp->addr + (y * temp->b + x * (temp->a / 8));
	*(unsigned int *)dst = color;
}

int	move(int key, t_map *map)
{
	if (key == ESCAPE)
		return (mlx_loop_end(map->mlx->mlx));
	return (0);
}

int	create_rgb(int a, int b, int c)
{
	return (0 << 24 | a << 16 | b << 8 | c);
}


int	create_trgb(int tab[3])
{
	return (0 << 24 | tab[0] << 16 | tab[1] << 8 | tab[2]);
}

void	destroywindows(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

void	backgroundcolor(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{
	int	i;
	int	j;
	int	ceiling;
	int	floor;

	i = -1;
	ceiling = create_trgb(map->ceiling);
	floor = create_trgb(map->floor);
	while (++i < data->win_w)
	{
		j = -1;
		while (++j < data->win_h)
		{
			if (j < data->win_h / 2 && j < data->win_w / 2)
				my_mlx_pixel_put(temp, i, j, ceiling);
			else
				my_mlx_pixel_put(temp, i, j, floor);
		}
	}
}

int	initmlx(t_map *map, t_mlx *mlx, t_data *data, t_temp *temp)
{
	int	z;

	z = 0;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx_get_screen_size(mlx->mlx, &data->win_w, &data->win_h);
	ft_printf("data->win_w:%i, data->win_h:%i\n", data->win_w, data->win_h);
	mlx->win = mlx_new_window(mlx->mlx, data->win_w, data->win_h, "cub3D");
	if (!mlx->win)
		return (ft_free((void **)&mlx->mlx), 1);
	temp->img = mlx_new_image(mlx->mlx, data->win_w, data->win_h);
	if (!temp->img)
		return (destroywindows(mlx), 1);
	temp->addr = mlx_get_data_addr(temp->img, &temp->a, &temp->b, &temp->c);
	backgroundcolor(map, mlx, data, temp);
	return (0);
}

void	fillminimap(t_map *map, t_data *data, t_temp *temp, int size)
{
	int i = 0;
	int j = 0;
	while (j < temp->width)
	{
		i = 0;
		while (i < temp->height)
		{
			// ft_printf("i/map->height:%i, j/map->maxlen:%i\n", i/map->height, j/map->maxlen);
			if (map->map[i / (temp->height / map->height)][j / (temp->height / map->maxlen)] == ' ')
				my_mlx_pixel_put(temp, j , i, create_rgb(134, 163, 184));
			if (map->map[i / (temp->height / map->height)][j / (temp->height / map->maxlen)] == '0')
				my_mlx_pixel_put(temp, j , i, create_rgb(232, 210, 166));
			if (map->map[i / (temp->height / map->height)][j / (temp->height / map->maxlen)] == 'N')
				my_mlx_pixel_put(temp, j , i, create_rgb(244, 132, 132));
			i++;
		}
		j++;
	}
}


// void	fillminimap(t_map *map, t_data *data, t_temp *temp, int size)
// {
// 	int i = 0;
// 	int j = 0;
// 	while (j < temp->width * temp->height)
// 	{
// 		if (map->map[i / temp->width][j % temp->width] == ' ')
// 			my_mlx_pixel_put(temp, j , i, create_rgb(134, 163, 184));
// 		if (map->map[i / temp->width][j % temp->width] == '0')
// 			my_mlx_pixel_put(temp, j , i, create_rgb(232, 210, 166));
// 		if (map->map[i / temp->width][j % temp->width] == 'N')
// 			my_mlx_pixel_put(temp, j , i, create_rgb(244, 132, 132));
// 		j++;
// 	}
// }

void	ft_printtomlx(t_map *map, t_mlx *mlx, t_data *data)
{
	t_temp	mini;

	int size;
	size = 25;
	ft_printf("realmap:%i|%i\n", map->maxlen *= 2, map->height *= 2);
	ft_printf("window:%i|%i\n", data->win_w, data->win_h);
	ft_printf("size=%i\n", size);
	mini.width = map->maxlen * size;
	mini.height = map->height * size;
	ft_printf("minimap:%i|%i\n", mini.width, mini.height);
	mini.img = mlx_new_image(mlx->mlx, mini.width, mini.height);
	mini.addr = mlx_get_data_addr(mini.img, &mini.a, &mini.b, &mini.c);
	fillminimap(map, data, & mini, size);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mini.img, 0, 0);
}

// void	ft_startgame(t_map *map, t_mlx *mlx, t_data *data)
// {

// }

void	set_colors(t_rgb (**colors), t_map *map)
{
	(*colors)[0] = (t_rgb){.r = map->ceiling[0], .g = map->ceiling[1], .b = map->ceiling[2]};
	(*colors)[1] = (t_rgb){.r = map->floor[0], .g = map->floor[1], .b = map->floor[2]};
}

int	ft_game(t_map *map, t_mlx *mlx, t_data *data)
{
	t_rgb *colors[2];
	set_colors(& colors[2], map);
	t_temp temp;
	map->mlx = mlx;
	map->data = data;
	data->mlx = mlx;
	if (initmlx(map, mlx, data, &temp))
		return (1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, temp.img, 0, 0);
	mlx_key_hook(mlx->win, &move, map);
	ft_printtomlx(map, mlx, data);
	// ft_startgame(map, mlx, data);
	mlx_loop(mlx->mlx);
	mlx_destroy_image(mlx->mlx, temp.img);
	destroywindows(mlx);
	return (0);
}


/*

ETAPE 1: mini so long

ETAPE 2: tourner camera

ETAPE 3: ligne de 10pixel bien droit 

ETAPE 4: la ligne doit mtn sarreter au 1er mur

ETAPE 5: ligne x fov




*/