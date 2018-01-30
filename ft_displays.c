/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:50:37 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:30:36 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_lstroomdump(t_list **list)
{
	t_list		*l;

	if (!list || !*list)
	{
		ft_putstr("(null)\n");
		return ;
	}
	l = *list;
	while ((*list))
	{
		if ((*list)->content)
			ft_putstr((char*)((t_room*)(*list)->content)->name);
		else
			ft_putstr(" (null) ");
		ft_putstr(" -> ");
		*list = (*list)->next;
	}
	ft_putstr(" NULL\n");
	*list = l;
}

void	dispnode(t_room *t)
{
	ft_printf("name : %s\t; ", t->name);
	ft_printf(" x : %d\t; ", t->x);
	ft_printf("y : %d\t\t", t->y);
	ft_lstroomdump(&(t->pipes));
}

void	ft_lstndump(t_list **list)
{
	t_list		*l;

	if (!list)
	{
		ft_putstr("(null)\n");
		return ;
	}
	l = *list;
	while ((*list))
	{
		ft_printf("[%d]\t", (*list)->content_size);
		if ((*list)->content)
			dispnode((*list)->content);
		else
			ft_putstr(" (null) ");
		*list = (*list)->next;
	}
	ft_putstr("NULL\n");
	*list = l;
}

void	ft_pathdump(t_list **list)
{
	t_list *l;

	if (!(list))
	{
		ft_putstr("(null)\n");
		return ;
	}
	l = *list;
	while ((*list))
	{
		if ((*list)->content)
			ft_lstndump((*list)->content);
		else
			ft_putstr(" (null) ");
		*list = (*list)->next;
	}
	ft_putstr("NULL\n");
	*list = l;
}
