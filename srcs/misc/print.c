/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:20:44 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/01 04:22:31 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


# define SPACES " \t"
# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

char	*colored(char *str, int value)
{
	int i = 0;

	while(str[i] && value)
	{
		if (str[i] == '1')
			printf("%s%c%s", "\033[7;35m", ' ', RESET);
		if (str[i] == '0')
			printf("%s%c%s", "\033[7;32m", ' ', RESET);
		if (str[i] == ' ')
			printf("%s%c%s", "\033[7;33m", ' ', RESET);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W') 
			printf("%s%c%s", "\033[7;32m", str[i], RESET);
		if (str[i] == 'R')
			printf("%s%c%s", "\033[7;31m", ' ', RESET);
		i++;
	}
	while(str[i] && !value)
	{
		if (str[i] == '1')
			printf("%s%c%s", MAGENTA, str[i], RESET);
		if (str[i] == '0')
			printf("%s%c%s", "\033[5;32m", str[i], RESET);
		if (str[i] == ' ')
			printf("%s%c%s", "\033[7;33m", str[i], RESET);
		if (str[i] == 'R')
			printf("%s%c%s", "\033[7;31m", ' ', RESET);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W') 
			printf("%s%c%s", WHITE, str[i], RESET);
		i++;
	}
	return (NULL);
	

}

void	ft_printmap(char **tab, int value)
{
	int	i;
	int	j;
	int	size;
	int	max;
	int	var;
	int	temp;

	static char *color[6] = {
		YELLOW, RED, GREEN, CYAN, BLUE, MAGENTA};
	var = 0;
	i = -1;
	j = -1;
	size = -1;
	max = 0;
	printf("\t\tMAP %i\n", value);
	while (tab[++size])
	{
		i = ft_strlen(tab[size]);
		if (i > max)
			max = i;
	}
	temp = max;
	printf(" ");
	while (++j < max)
	{
		printf("%s%i%s", color[var], j, RESET);
		if (j == 9)
		{
			if (var++ == 5)
				var = 0;
			j = -1;
			max -= 10;
		}
	}
	printf("\n");
	i = -1;
	j = 0;
	var = 0;
	while (tab[++i])
	{
		int val = ft_strlen(tab[i]);
		if (val == temp)
		{
			printf("%s%i%s", color[var], j, RESET);
			colored(tab[i], value);
			printf("%s%i%s\n", color[var], j, RESET);
		}
		else
		{
			printf("%s%i%s\n", color[var], j, RESET);
			colored(tab[i], value);
			printf("%*c%s%i%s\n", temp - (int)ft_strlen(tab[i]), ' ', color[var], j, RESET);
		}
		if (j++ == 9)
		{
			if (var++ == 5)
				var = 0;
			j = 0;
		}
	}
	printf(" ");
	j = -1;
	var = 0;
	max = temp;
	while (++j < max)
	{
		printf("%s%i%s", color[var], j, RESET);
		if (j == 9)
		{
			if (var++ == 5)
				var = 0;
			j = -1;
			max -= 10;
		}
	}
	printf("\n");
}

char	*c(int n)
{
	int len;
	static char *color[6] = {
		YELLOW, RED, GREEN, CYAN, BLUE, MAGENTA};

	len = 0;
	while (n > 10)
	{
		n /= 10;
		if (len++ == 5)
			len = 0;
	}
	return (color[len]);
}

