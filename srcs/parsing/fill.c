/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:44:27 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/01 00:47:03 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fillpathcolors(t_map *map, char *str, int index)
{
	if (index > 3)
	{
		index -= 4;
		if (!map->colors[index])
		{
			map->colors[index] = ft_strdup(str);
			map->type_colors[index] = index;
		}
		else
			return (0);
		return (1);
	}
	if (!map->path[index])
	{
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

	static char *match[6] = {
		"NO", "SO", "WE", "EA", "F", "C"};
	i = -1;
	k = 0;
	j = 0;
	while (tab[++i])
	{
		temp = ft_split(tab[i], SPACES, &j);
		if (!temp)
			return (ft_freetab(tab), 1);
		if (j != 2)
			return (ft_freetab(tab), ft_freetab(temp), 1);
		j = -1;
		while (match[++j])
			if (!ft_strcmp(temp[0], match[j]))
				k += fillpathcolors(map, temp[1], j);
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
	return (NULL);
}

