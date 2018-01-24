/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:18:53 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/24 14:16:39 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_start_end(t_list **list, t_list **start, t_list **end)
{
	t_list		*l;
	int			s;
	int			e;

	s = 0;
	e = 0;
	if (!list)
		return (0);
	l = *list;
	while (*list)
	{
		if ((*list)->content_size == 1)
		{
			if (s == 1)
				return (0);
			*start = *list;
			s = 1;
		}
		if ((*list)->content_size == 2)
		{
			if (e == 1)
				return (0);
			*end = *list;
			e = 1;
		}
		*list = (*list)->next;
	}
	*list = l;
	return (1);
}

int		get_children(t_room *room)
{
	t_list		*tmp;

	tmp = room->pipes;
	while (tmp)
	{
		ft_printf("%s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

int		solver(t_list **t)
{
	t_list		*start;
	t_list		*end;
	//int			max;

	if (!get_start_end(t, &start, &end))
		return (0);
	get_children(start->content);
	ft_printf("%d\n", ft_lstsize(((t_room*)(*start).content)->pipes));
	ft_printf("%d\n", ft_lstsize(((t_room*)(*end).content)->pipes));
	return (1);
}
