/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:44:18 by arobion           #+#    #+#             */
/*   Updated: 2018/01/31 12:33:17 by arobion          ###   ########.fr       */
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

void	freenames(char ***names, t_list **paths)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
	j = 0;
	tmp = *paths;
	while (i < ft_lstsize(*paths))
	{
		j = 0;
		while (j <= ft_lstsize(tmp->content) - 1)
		{
			free(names[i][j]);
			j++;
		}
		free(names[i]);
		i++;
	}
	free(names);
}

void	freetabs(int **tabs, t_list **paths)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *paths;
	while (i < ft_lstsize(*paths))
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}
