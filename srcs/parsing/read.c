/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:42:13 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/01 13:15:21 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (ft_error(ERR_FDFAIL, RED, map), NULL);
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
			break ;
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
		return (ft_error("fail", YELLOW, map), NULL);
	ret = NULL;
	while (buff && lineempty(buff))
	{
		ft_free((void **)&buff);
		buff = get_next_line(map->filefd, 0);
	}
	while (buff)
	{
		if (lineempty(buff))
			return (free(buff), free(ret), ft_error(ERR_INVALID, YELLOW, map),
				NULL);
		x = ft_strlen(buff);
		if (x > map->maxlen)
			map->maxlen = x - 1;
		ret = ft_realloc(ret, buff);
		ft_free((void **)&buff);
		buff = get_next_line(map->filefd, 0);
	}
	close(map->filefd);
	return (ret);
}
