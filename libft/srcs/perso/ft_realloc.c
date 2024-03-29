/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:47:16 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/29 23:21:25 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *s1, char *s2)
{
	char	*temp;
	size_t	s1len;
	size_t	s2len;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	temp = malloc(s1len + s2len + 1);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, s1);
	ft_strcpy(temp + s1len, s2);
	ft_free((void **)&s1);
	return (temp);
}

/*

< Makefile cat 
 ls > out 
 grep "lol"
 1  9 3 10 4 20 2
*/