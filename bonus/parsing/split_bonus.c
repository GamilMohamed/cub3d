/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:03:02 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/12 20:49:20 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static
char	*ft_strtsub(char const *str, int start, int end, int *size)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_calloc(sizeof(char) * ((*size) + 1), 1);
	if (!var)
		return (NULL);
	var[0] = ' ';
	while (((start + i) <= end) && str[i])
	{
		var[i + 1] = str[start + i];
		i++;
	}
	while (i < (*size))
		var[i++] = ' ';
	var[i] = '\0';
	return (var);
}

char	*fill(int *size)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(sizeof(char) * ((*size) + 1), 1);
	while (i < (*size))
		str[i++] = ' ';
	str[i] = 0;
	return (str);
}

static
char	**to_tab(char **tab, char const *s, char *charset, int *tabint[2])
{
	int	i;
	int	index;
	int	start;

	i = 0;
	index = 1;
	tab[0] = fill(tabint[1]);
	while (index < (*tabint)[0])
	{
		while (s[i] && ft_strchr(charset, s[i]))
			i++;
		start = i;
		while (s[i] && (!ft_strchr(charset, s[i])))
			i++;
		tab[index] = ft_strtsub(s, start, i, tabint[1]);
		if (!tab[index])
			return (ft_freetab(tab), NULL);
		index++;
	}
	tab[(*tabint)[0]] = fill(tabint[1]);
	return (tab);
}

char	**ft_specialit(char const *s, char *charset, int size)
{
	char	**tab;
	int		n;

	if (!s || !*s)
		return (ft_calloc(sizeof(char *) * 1, 1));
	n = ft_countdelim(s, charset);
	n++;
	tab = ft_calloc(sizeof(char *) * (n + 2), 1);
	if (!tab)
		return (NULL);
	tab = to_tab(tab, s, charset, (int *[2]){& n, & size});
	*(tab + n + 1) = NULL;
	return (tab);
}
