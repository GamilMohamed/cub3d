/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:57 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/01 23:25:47 by mgamil           ###   ########.fr       */
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

char	*multiplicator(t_map *map, char *src, char *dst, int size)
{
	int	i;
	int	j;
	int	count;
	static int	stop;

	i = -1;
	count = 0;
	while (src[++i])
	{
		j = -1;
		while (++j < (SIZE))
		{
			if (ft_strchr("NSEW", src[i]) && !stop)
			{
				dst[count++] = src[i];
				stop++;
			}
			else if (!ft_strchr("NSEW", src[i]))
				dst[count++] = src[i];
			else
				dst[count++] = '0';
		}
	}
	return (dst);
}

char	**expandmap(t_map *map)
{
	char	**tab;
	int		i;
	int		j;
	int		count;

	i = -1;
	count = 0;
	tab = ft_calloc(sizeof(char *) * (map->height * SIZE + 1), 1);
	while (map->map[++i])
	{
		j = -1;
		while (++j < (SIZE))
		{
			tab[count] = ft_calloc(sizeof(char) * (map->maxlen * SIZE + 1000), 1);
			multiplicator(map, map->map[i], tab[count], SIZE);
			count++;
		}
	}
	ft_freetab(map->map);
	return (tab);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx;
	t_data	data;

	map . mlx = & mlx;
	map . data = & data;
	ft_memset(&map, 0, sizeof(t_map));
	map.maxlen = 0;
	if (checkextension(ac, av[1]))
		return (EXIT_FAILURE);
	map.cubfile = readinfo(&map, &map.filefd, av[1]);
	if (!map.cubfile)
		return (EXIT_FAILURE);
	fillstruct(&map);
	ft_free((void **)&map.cubfile);
	map.cubfile = readmap(&map);
	if (!map.cubfile)
		return (ft_error(ERR_NO_MAP, YELLOW, &map));
	checkmap(&map);
	ft_printstruct(&map);
	ft_printf("valid map!\n");
	map.map = expandmap(& map);
	ft_printmap(map.map, 0);
	// ft_freetab(map.map);
	ft_game(&map, & mlx, & data);
	ft_freestruct_map(&map);
	return (0);
}


/*
check ft_specialit elle deconne

*/