/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:50:37 by arobion           #+#    #+#             */
/*   Updated: 2018/01/23 15:06:38 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dispnode(t_room *t)
{
	ft_printf("name : %s\t; ", t->name);
	ft_printf(" x : %d\t; ", t->x);
	ft_printf("y : %d\t\t", t->y);
	ft_lstdump(&(t->pipes));
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
