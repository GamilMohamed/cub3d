/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:25:19 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/17 23:09:54 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define TEMP 1

char	*multiplicator(char *src, char *dst)
{
	int			i;
	int			j;
	int			count;
	static int	stop;

	i = -1;
	count = 0;
	while (src[++i])
	{
		j = -1;
		while (++j < (TEMP))
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
	tab = ft_calloc(sizeof(char *) * (map->height * TEMP + 1), 1);
	while (map->map[++i])
	{
		j = -1;
		while (++j < (TEMP))
		{
			tab[count] = ft_calloc(sizeof(char) * (map->maxlen * TEMP + 1), 1);
			multiplicator(map->map[i], tab[count]);
			count++;
		}
	}
	ft_freetab(map->map);
	map->maxlen *= TEMP;
	map->height *= TEMP;
	return (tab);
}

// int	checkaround(t_map *map, int x, int y, char **tab)
// {
// 	int	count;

// 	count = 0;
// 	if (x < map->height - 1 && y < map->maxlen - 1)
// 	{
// 		if (tab[x + 1][y] != ' ' && tab[x + 1][y] != '1')
// 		{
// 			tab[x + 1][y] = 'R';
// 			count++;
// 		}
// 		if (tab[x][y + 1] != ' ' && tab[x][y + 1] != '1')
// 		{
// 			tab[x][y + 1] = 'R';
// 			count++;
// 		}
// 	}
// 	if (x > 0 && y > 0)
// 	{
// 		if (tab[x - 1][y] != ' ' && tab[x - 1][y] != '1')
// 		{
// 			tab[x - 1][y] = 'R';
// 			count++;
// 		}
// 		if (tab[x][y - 1] != ' ' && tab[x][y - 1] != '1')
// 		{
// 			tab[x][y - 1] = 'R';
// 			count++;
// 		}
// 	}
// 	return (count);
// }

int	checkaround(t_map *map, int x, int y, char **tab)
{
	if (x < map->height - 1 && y < map->maxlen - 1)
		if ((tab[x + 1][y] != ' ' && tab[x + 1][y] != '1') || (tab[x][y
				+ 1] != ' ' && tab[x][y + 1] != '1'))
			return (ft_freetab(tab), 1);
	if (x > 0 && y > 0)
		if ((tab[x - 1][y] != ' ' && tab[x - 1][y] != '1') || (tab[x][y
				- 1] != ' ' && tab[x][y - 1] != '1'))
			return (ft_freetab(tab), 1);
	return (0);
}

void	check_surroundings(t_map *map)
{
	int		i;
	int		j;
	int		total;

	total = 0;
	i = -1;
	map->map = ft_specialit(map->cubfile, "\n", map->maxlen + 2);
	map->height = ft_tablen(map->map);
	map->maxlen += 2;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->maxlen)
			if (map->map[i][j] == ' ')
				if (checkaround(map, i, j, map->map))
					ft_error(ERR_MAP, YELLOW, map);
	}
}

void	checkchars(t_map *map)
{
	int			i;
	int			wrong;
	char		*str;
	static int	var;
	int			clock;

	var = 0;
	i = 0;
	wrong = 0;
	clock = 0;
	str = map->cubfile;
	while (str && str[i])
	{
		if (ft_strchr("NSEW", str[i]))
			var++;
		else if (!ft_strchr(" 10QD\n", str[i]))
			wrong++;
		else if (str[i] == 'Q')
			clock++;
		i++;
	}
	if (var != 1 || wrong || clock > 1)
	{
		printf("var = %d, wrong = %d, clock = %d\n", var, wrong, clock);
		ft_error(ERR_CHARS, YELLOW, map);
	}
}

void	checkmap(t_map *map)
{
	checkchars(map);
	check_surroundings(map);
	map->map = expandmap(map);
	// int size = (map->maxlen * map->height) / 64;
	// if (map->maxlen * size >= WIDTH || map->height * size >= HEIGHT)
		// ft_error(ERR_MAP_B, YELLOW, map);
}
