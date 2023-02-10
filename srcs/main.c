/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:57 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/10 18:58:40 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				map->data->player_pos.x = i + 0.5;
				map->data->player_pos.y = j + 0.5;
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


int	main(int ac, char **av)
{
	t_map	*map;
	t_mlx	mlx;
	t_data	data;

	if (checkextension(ac, av[1]))
		return (EXIT_FAILURE);
	map = ft_calloc(sizeof(t_map) * 1, 1);
	map->data = ft_calloc(sizeof(t_data) * 1, 1);
	map->mlx = ft_calloc(sizeof(t_mlx) * 1, 1);
	map->cubfile = readinfo(map, & map->filefd, av[1]);
	if (!map->cubfile)
		return (EXIT_FAILURE);
	fillstruct(map);
	ft_free((void **)& map->cubfile);
	map->cubfile = readmap(map);
	if (!map->cubfile)
		return (ft_error(ERR_NO_MAP, YELLOW, map));
	checkmap(map);
	get_positions(map, & data);
	ft_printstruct(map);
	ft_printmap(map->map, 0);
	ft_game(map, map->mlx, map->data);
	ft_freetab(map->map);
	ft_freestruct_map(map);
	// free(map->data);
	// free(map->mlx);
	return (0);
}
