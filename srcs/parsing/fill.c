/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:44:27 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/11 04:42:46 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_color_tab(int (*rgb)[3], char *color)
{
	int	tmp;
	int	i;

	i = 0;
	while (*color)
	{
		tmp = 0;
		while (ft_isdigit(*color))
		{
			tmp = (tmp * 10) + *color - '0';
			if (tmp > 255)
				return (EXIT_FAILURE);
			color++;
		}
		if (i != 2 && *color != ',')
			return (EXIT_FAILURE);
		color++;
		(*rgb)[i++] = tmp;
	}
	return (EXIT_SUCCESS);
}

int	fillpathcolors(t_map *map, char *str, int index)
{
	char	*temp;

	if (index > 3)
	{
		temp = ft_strjoin(str, "\n");
		index -= 4;
		if (index == 1)
		{
			if (set_color_tab(&map->ceiling, temp))
				return (ft_free((void **)& temp), 0);
		}
		else
		{
			if (set_color_tab(&map->floor, temp))
				return (ft_free((void **)& temp), 0);
		}
		return (ft_free((void **)& temp), 1);
	}
	if (!map->path[index])
	{
		int fd = open(str, O_RDONLY);
		if (fd == -1)
			return (0);
		else
			close(fd);
		map->path[index] = ft_strdup(str);
		map->type_path[index] = index;
	}
	else
		return (0);
	return (1);
}

int	filldirections(t_map *map, char **tab)
{
	int		i;
	int		j;
	int		k;
	char	**temp;

	static const char *match[6] = {
		"NO", "SO", "WE", "EA", "F", "C"};
	i = -1;
	k = 0;
	j = 0;
	while (tab[++i])
	{
		temp = ft_split(tab[i], SPACES, &j);
		ft_printtab(temp);
		if (!temp)
			return (ft_freetab(tab), 1);
		if (j != 2)
			return (ft_freetab(tab), ft_freetab(temp), 1);
		j = -1;
		while (++j < 6)
		{
			printf("%i\n", j);
			if (!ft_strcmp(temp[0], match[j]))
				k += fillpathcolors(map, temp[1], j);
		}
		ft_freetab(temp);
	}
	if (k != 6)
		return (ft_freetab(tab), 1);
	return (0);
}

void	*fillstruct(t_map *map)
{
	char	**tab;
	int		size;

	tab = ft_split(map->cubfile, "\n", &size);
	if (!tab)
		return (ft_free((void **)&map->cubfile), NULL);
	if (filldirections(map, tab))
		ft_error(ERR_KEYS, YELLOW, map);
	ft_freetab(tab);
	// updatecolors(map);
	return (NULL);
}
