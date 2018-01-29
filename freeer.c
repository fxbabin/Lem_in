/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:44:18 by arobion           #+#    #+#             */
/*   Updated: 2018/01/29 18:57:18 by arobion          ###   ########.fr       */
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

void	freenode(t_room *t)
{
	free((void*)t->name);
	ft_lstdel(&(t->pipes), ft_eldel);
	free((void*)t->pipes);
	free(t);
}

void	freenode2(t_room *t)
{
	free((void*)t->name);
//	ft_lstdel(&(t->pipes), ft_eldel);
	free((void*)t->pipes);
	free(t);
}

void	ft_lstnfree(t_list **list)
{
	t_list		*tmp;

	if (!list || !*list)
		return ;
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

void	ft_lstnfree2(t_list **list)
{
	t_list		*tmp;

	if (!list || !*list)
		return ;
	while ((*list))
	{
		if ((*list)->content)
			freenode2((*list)->content);
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	free(*list);
}
