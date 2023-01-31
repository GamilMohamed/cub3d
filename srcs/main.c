/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:57 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/31 03:26:44 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_printstruct(t_map *map)
{
	int		i;
	char	**tab  = ft_split(map->cubfile, "\n", & i);

	i = 0;
	ft_printlist(map->files);
	printf("\t\tMAP\t\t\n");
	ft_printmap(tab, 0);
	printf("\t\t***\n");
}

int	checktypes(t_rr *head)
{
	t_rr	*temp;
	t_rr	*temp2;
	int		i;

	i = -1;
	temp = head;
	while (temp)
	{
		i = temp->type;
		temp2 = temp->next;
		while (temp2)
		{
			if (i == temp2->type)
				return (1);
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return (0);
}

int		filldirections(t_map *map, char **tab)
{
	int		i;
	int		j;
	int		k;
	char	**temp;

	static char *match[6] = {
		"NO", "SO", "WE", "EA", "F", "C"};
	map->files = 0;
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
		{
			if (!ft_strcmp(temp[0], match[j]))
				k += ft_lstadd_back_rr(&map->files,
										ft_lstnew_rr(ft_strdup(temp[1]), j));
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
		ft_error("invalid!!", YELLOW, map);
	ft_freetab(tab);
	if (checktypes(map->files))
		ft_error("doublons!!", YELLOW, map);
	return (NULL);
}

int	lineempty(char *buff)
{
	int	i;

	i = 0;
	while (ft_isspace(buff[i]))
		i++;
	return (buff[i] == 0);
}

char	*readinfo(t_map *map, int *fd, char *str)
{
	char	*buff;
	char	*ret;
	int		i;

	i = 0;
	(*fd) = open(str, O_RDONLY);
	if ((*fd) == -1)
		return (ft_error("can't open !!", RED, map), NULL);
	buff = get_next_line((*fd), 0);
	ret = NULL;
	while (buff && i < 6)
	{
		if (!lineempty(buff))
		{
			ret = ft_realloc(ret, buff);
			i++;
		}
		ft_free((void **)&buff);
		if (i == 6)
			break;
		buff = get_next_line((*fd), 0);
	}
	ft_free((void **)&buff);
	return (ret);
}

char	*readmap(t_map *map)
{
	char	*buff;
	char	*ret;
	int		i;
	int		x;

	i = 0;
	x = 0;
	buff = get_next_line(map->filefd, 0);
	if (!buff)
		return (ft_error("where is the map?!", YELLOW, map), NULL);
	ret  = NULL;
	while (buff && lineempty(buff))
	{
		ft_free((void **)&buff);
		buff = get_next_line(map->filefd, 0);
	}
	while (buff)
	{
		if (lineempty(buff))
			return (free(buff), free(ret), ft_error("new line in map found!", YELLOW, map), NULL);
		x = ft_strlen(buff);
		if (x > map->maxlen)
			map->maxlen = x;
		ret = ft_realloc(ret, buff);
		ft_free((void **)& buff);
		buff = get_next_line(map->filefd, 0);
	}
	close(map->filefd);
	return (ret);
}

int	ft_tablen(char **tab)
{
	if (!tab || !*tab)
		return (0);
	int i = 0;
	while (tab[i])
		i++;
	return (i);
}


int	checkaround(t_map *map, int x, int y, char **tab)
{
	int count = 0;
	if (x != 0 && y != 0 && x != map->height - 1 && y != map->maxlen - 1)
	{
		if (tab[x][y - 1] != ' ' && tab[x][y - 1] != '1')
			return (tab[x][y - 1] = 'R', 1);
		if (tab[x][y + 1] != ' ' && tab[x][y + 1] != '1')
			return (tab[x][y + 1] = 'R', 1);
		if (tab[x + 1][y] != ' ' && tab[x + 1][y] != '1')
			return (tab[x + 1][y] = 'R', 1);
		if (tab[x - 1][y] != ' ' && tab[x - 1][y] != '1')
			return (tab[x - 1][y] = 'R', 1);
	}
	else if (x == 0)
	{
		if (tab[x + 1][y] != ' ' && tab[x + 1][y] != '1')
			return (tab[x + 1][y] = 'R', 1);
	}
	else if (y == 0)
	{
		if (tab[x][y + 1] != ' ' && tab[x][y + 1] != '1')
			return (tab[x][y + 1] = 'R', 1);
	}
	else if (x == map->height - 1)
	{
		if (tab[x - 1][y] != ' ' && tab[x - 1][y] != '1')
			return (tab[x - 1][y] = 'R', 1);
	}
	else if (y == map->maxlen - 1)
	{
		if (tab[x][y - 1] != ' ' && tab[x][y - 1] != '1')
			return (tab[x][y - 1] = 'R', 1);
	}
	return (0);
}

void	*checkmap(t_map *map)
{
	char	**tab;
	int		size;
	int		i;
	int		j;
	int		total;
	int		lenline;

	total = 0;

	i = -1;
	tab = ft_specialit(map->cubfile, "\n", map->maxlen + 2);
	map->height = ft_tablen(tab);
	map->maxlen += 2;
	ft_printf("%i|%i\n", map->height, map->maxlen);
	ft_printmap(tab, 1);
	while (++i < map->height)
	{
		j = -1;
		lenline = ft_strlen(tab[i]);
		while (++j < map->maxlen)
		{
			if (tab[i][j] == ' ')
				total += checkaround(map ,i, j, tab);
		}
	}
	ft_printmap(tab, 0);
	printf("nombre de failles: %i\n", total);
	ft_freetab(tab);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_map	map;

	ft_memset(& map, 0, sizeof(t_map));
	map.maxlen = 0;
	if (checkextension(ac, av[1]))
		return (EXIT_FAILURE);
	map.cubfile = readinfo(& map, & map.filefd, av[1]);
	if (!map.cubfile)
		return (EXIT_FAILURE);
	fillstruct(&map);
	ft_free((void **) & map.cubfile);
	map.cubfile = readmap(& map);
	// ft_printstruct(&map);
	checkmap(&map);
	ft_freerr(map.files);
	ft_freestruct_map(& map);
	return (0);
}
