/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:57 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/30 02:36:39 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_printstruct(t_map *map)
{
	int	i;

	i = 0;
	ft_printlist(map->files);
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
				return (ft_printf("doublons!\n"));
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return (0);
}

void	*filldirections(t_map *map, char **tab)
{
	static char				*match[6] = {
		"NO", "SO", "WE", "EA", "F", "C"};
	int						i;
	int						j;
	int						k;
	char					**temp;

	map->files = 0;
	i = -1;
	k = 0;
	while (++i < 6)
	{
		temp = ft_split(tab[i], SPACES, &j);
		if (j != 2)
			return (ft_error("args are not correct", RED), NULL);
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
		ft_printf("%rwrong info!!\n%0");
	return (NULL);
}

void	*fillstruct(t_map *map)
{
	char	**tab;
	int		size;

	tab = ft_split(map->cubfile, "\n", &size);
	if (!tab)
		return (ft_free((void **)&map->cubfile), NULL);
	filldirections(map, tab);
	if (checktypes(map->files))
		ft_printf("%rdoublons !!\n%0");
	ft_freetab(tab);
	return (NULL);
}

char	*readinfo(char *str)
{
	int		fd;
	char	*buff;
	char	*ret;
	int		i;

	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_error("can't open !!", RED), NULL);
	buff = get_next_line(fd, 0);
	ret = NULL;
	while (buff && i < 6)
	{
		if (ft_strcmp(buff, "\n"))
			i++;
		ret = ft_realloc(ret, buff);
		ft_free((void **)&buff);
		buff = get_next_line(fd, 0);
	}
	ft_free((void **)&buff);
	close(fd);
	return (ret);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (checkextension(ac, av[1]))
		return (EXIT_FAILURE);
	map.cubfile = readinfo(av[1]);
	fillstruct(&map);
	ft_printstruct(&map);
	ft_freerr(map.files);
	get_next_line(1, 1);
	free(map.cubfile);
	return (0);
}
