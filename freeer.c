/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:44:18 by arobion           #+#    #+#             */
/*   Updated: 2018/01/25 21:39:28 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	freechar2(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

/*void	ft_eldel(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}*/

/*void	ft_roomdel(void *content, size_t content_size)
{
 	(void)content;
	(void)content_size;
}*/

void	freenode(t_room *t)
{
	free((void*)t->name);
	ft_lstdel(&(t->pipes), ft_eldel);
	free((void*)t->pipes);
	free(t);
}

void	ft_lstnfree(t_list **list)
{
	t_list		*l;
	t_list		*tmp;

	if (!list || !*list)
		return ;
	l = *list;
	while ((*list))
	{
		if ((*list)->content)
			freenode((*list)->content);
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	free(*list);
}
