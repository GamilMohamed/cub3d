/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:57 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/17 23:01:32 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_printstruct(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
		ft_printf("%i->[%s]\n", i, map->path[i]);
	i = -1;
	printf("\t\tCEILING\t\t\n");
	while (++i < 3)
		ft_printf("%i,", map->ceiling[i]);
	printf("\n");
	printf("\t\tFLOOR\t\t\n");
	i = -1;
	while (++i < 3)
		ft_printf("%i,", map->floor[i]);
	printf("\t\tMAP\t\t\n");
	ft_printmap(map->map, 0);
	ft_printmap(map->map, 1);
	printf("\t\t***\n");
}

void	get_positions(t_map *map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr("NSEW", map->map[i][j]))
			{
				data->player_pos.x = i + 0.5;
				data->player_pos.y = j + 0.5;
				map->pos.x = (double)i + 0.5;
				map->pos.y = (double)j + 0.5;
				map->data->player = map->map[i][j];
				map->map[i][j] = '0';
			}
			if (map->map[i][j] == 'Q')
			{
				printf("Q found\n");
				map->map[i][j] = '0';
				map->pos_q.y = (double)i;
				map->pos_q.x = (double)j;
			}
			j++;
		}
		i++;
	}
}

void	ft_stoval(char *str, int n, int start, int len)
{
	int				i;
	unsigned int	nb;

	str[len] = 0;
	nb = n;
	i = start;
	while (--len >= i)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
}


char	*get_file(char *buff, char *str, int *index)
{
	static char	*extension[2] = {".JPG", ".jpg"};
	char		copy[1024];
	int			year;

	year = 2022;
	while (*index < 2)
	{
		year = 2013;
		while (year < 2024)
		{
			ft_strcpy(copy, buff);
			ft_stoval(buff, year++, 26, 26 + 4);
			ft_strcat(buff, "/");
			ft_strcat(buff, str);
			ft_strcat(buff, extension[*index]);
			if (access(buff, F_OK) != -1)
				return (ft_strdup(buff));
		}
		(*index)++;
	}
	return (printf("%sfile not found%s\n", RED, RESET), NULL);
}

void	exec(char *file, char buff[3][1024], char **env)
{
	if (fork() == 0)
		execve("/usr/bin/cp", (char *[]){"/usr/bin/cp", file, "./stud", NULL},
				env);
	wait(NULL);
	if (fork() == 0)
		execve("/usr/bin/convert", (char *[]){"/usr/bin/convert", buff[1],
				"-resize", "64x64", buff[2], NULL}, env);
	wait(NULL);
}

int	extension(t_map *map, char *str, char **env)
{
	static char	*extension[2] = {".JPG", ".jpg"};
	char	buff[3][1024];
	char	*file;
	int		index;

	if (!str)
		return (0);
	ft_strcpy(buff[0], "/sgoinfre/photos_students/");
	file = get_file(buff[0], str, &index);
	if (!file)
		return (0);
	ft_strcpy(buff[1], "./stud/");
	ft_strcat(buff[1], str);
	ft_strcat(buff[1], extension[index]);
	ft_strcpy(buff[2], "./stud/");
	ft_strcat(buff[2], str);
	ft_strcat(buff[2], ".xpm");
	exec(file, buff, env);
	ft_free((void **)& map->path[0]);
	map->path[0] = ft_strdup(buff[2]);
	return (unlink(buff[1]), 1);
}

int	main(int ac, char **av, char **env)
{
	t_map	*map;
	t_data	data;

	if (checkextension(ac, av[1]))
		return (EXIT_FAILURE);
	map = ft_calloc(sizeof(t_map) * 1, 1);
	map->data = ft_calloc(sizeof(t_data) * 1, 1);
	map->mlx = ft_calloc(sizeof(t_mlx) * 1, 1);
	map->cubfile = readinfo(map, &map->filefd, av[1]);
	if (!map->cubfile)
		return (EXIT_FAILURE);
	fillstruct(map);
	extension(map, av[2], env);
	ft_free((void **)&map->cubfile);
	map->cubfile = readmap(map);
	if (!map->cubfile)
		return (ft_error(ERR_NO_MAP, YELLOW, map), 1);
	checkmap(map);
	get_positions(map, &data);
	// ft_printmap(map->map, 0);
	ft_game(map, map->mlx, map->data);
	ft_freetab(map->map);
	ft_freestruct_map(map);
	return (0);
}
// ft_printstruct(map);
