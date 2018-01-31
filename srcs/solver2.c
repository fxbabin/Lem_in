/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:39:55 by arobion           #+#    #+#             */
/*   Updated: 2018/01/31 14:53:57 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_lstin(t_list **begin_list, void *data_ref, int (*cmp)(),
		size_t size)
{
	t_list		*tmp;

	if (!begin_list || !data_ref || !cmp)
		return (0);
	tmp = *begin_list;
	while (tmp)
	{
		if (!(*cmp)(tmp->content, data_ref, size))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		check_s_e(int s, int e)
{
	if (s == 1 && e == 1)
		return (1);
	else
		return (0);
}

int		get_start_end(t_list **list, t_list **start, t_list **end)
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
			*start = *list;
			s++;
		}
		if ((*list)->content_size == 2)
		{
			*end = *list;
			e++;
		}
		*list = (*list)->next;
	}
	*list = l;
	return (check_s_e(s, e));
}

void	ft_lstremovefirst(t_list **begin_list, void *content_ref,
		int (*cmp)(), size_t size)
{
	t_list		*tmp;

	if (*begin_list && !cmp((*begin_list)->content, content_ref, size))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
}

void	ft_lstpushlist(t_list **begin_list, t_list **add,\
		int (*cmp)(), size_t size)
{
	t_list		*tmp;

	if (!begin_list || !add)
		return ;
	tmp = *add;
	while (tmp)
	{
		if (!ft_lstin(begin_list, tmp->content, cmp, size))
			ft_lstpushback(begin_list, tmp->content, 0);
		tmp = tmp->next;
	}
}
