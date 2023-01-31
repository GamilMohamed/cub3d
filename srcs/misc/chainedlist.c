/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chainedlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:19:56 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/30 16:52:05 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_lstadd_back_rr(t_rr **lst, t_rr *var)
{
	t_rr	*begin;

	begin = *lst;
	if (!*lst)
		*lst = var;
	else
	{
		while (begin->next)
			begin = begin->next;
		begin->next = var;
	}
	return (1);
}

t_rr	*ft_lstnew_rr(char *name, int type)
{
	t_rr	*elem;

	elem = ft_calloc(sizeof(*elem), 1);
	if (!elem)
		return (NULL);
	elem->name = name;
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

void	ft_freerr(t_rr *node)
{
	t_rr	*temp;

	while (node)
	{
		ft_free((void **)&node->name);
		temp = node->next;
		ft_free((void **)&node);
		node = temp;
	}	
}

void	ft_printlist(t_rr *temp)
{
	t_rr	*head;

	head = temp;
	while (head)
	{
		if (head->type == 0)
			ft_printf("%yNO%0");
		if (head->type == 1)
			ft_printf("%ySO%0");
		if (head->type == 2)
			ft_printf("%yWE%0");
		if (head->type == 3)
			ft_printf("%yEA%0");
		if (head->type == 4)
			ft_printf("%mF%0");
		if (head->type == 5)
			ft_printf("%mC%0");
		ft_printf("\t{%s}\n", head->name);
		head = head->next;
	}
}
