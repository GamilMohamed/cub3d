/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:57 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/14 12:14:21 by mgamil           ###   ########.fr       */
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
			j++;
		}
		i++;
	}
}

char *get_file(char *buff, char *str, int *index)
{
	static char *extension[2] = {".JPG", ".jpg"};
	char	copy[1024];

	for (*index = 0; *index < 2; (*index)++)
	{
		ft_strcpy(copy, buff);
		ft_strcat(copy, extension[*index]);
		if (access(copy, F_OK) != -1)
			return (ft_strdup(copy));
	}
	return (printf("%sfile not found%s\n", RED, RESET), NULL);
}

int	extension(t_map *map, char *str, char *year, char **env)
{
	char	buff[1024];
	char	temp[1024];
	char	fin[1024];
	char 	*file;
	int 	index;
	char *extension[2] = {".JPG", ".jpg"};

	if (!str || !year)
		return 0;
	ft_strcpy(buff, "/sgoinfre/photos_students/");
	ft_strcat(buff, year);
	ft_strcat(buff, "/");
	ft_strcat(buff, str);
	file = get_file(buff, str, & index);
	if (!file)
		return (0);
	ft_strcpy(temp, "./stud/");
	ft_strcat(temp, str);
	ft_strcat(temp, extension[index]);
	ft_strcpy(fin, "./stud/");
	ft_strcat(fin, str);
	ft_strcat(fin, ".xpm");
	if (fork() == 0)
		execve("/usr/bin/cp", (char *[]){"/usr/bin/cp", file, "./stud", NULL}, env);
	wait(NULL);
	if (fork() == 0)
		execve("/usr/bin/convert", (char *[]){"/usr/bin/convert", temp, "-resize", "64x64", fin, NULL}, env);
	wait(NULL);
	map->path[0] = ft_strdup(fin);
	unlink(temp);
	return (1);
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
	extension(map, av[2], av[3], env);
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
