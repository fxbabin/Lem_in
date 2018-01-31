/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:33:23 by arobion           #+#    #+#             */
/*   Updated: 2018/01/31 16:03:37 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_listss(t_list *paths)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = paths;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		free(paths);
		paths = tmp2;
		tmp = tmp2;
	}
	free(paths);
}

void			freeit(t_list *path)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = path;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		free_listss(path->content);
		free(path);
		path = tmp2;
		tmp = tmp2;
	}
	free_listss(path->content);
	free(path);
}

void			free_this(t_list *l)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = l;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		free(l);
		l = tmp2;
		tmp = tmp2;
	}
	free(l);
}
