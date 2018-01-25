/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:18:53 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/25 16:58:33 by fbabin           ###   ########.fr       */
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

static int		ft_lstin(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list		*tmp;

	if (!begin_list || !data_ref || !cmp)
		return (0);
	tmp = *begin_list;
	while (tmp)
	{
		if (!(*cmp)(tmp->content, data_ref, sizeof(data_ref)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		get_children(t_list **t, t_list **visited, t_room *room)
{
	t_list		*tmp;

	tmp = room->pipes;
	while (tmp)
	{
		if (!ft_lstin(visited, tmp->content, ft_memcmp))
		{
			ft_lstpushback(t, (t_room*)tmp->content, 0);
			ft_lstpushback(visited, (t_room*)tmp->content, 0);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			ft_lstremovefirst(t_list **begin_list, void *content_ref,
		int (*cmp)())
{
	t_list		*tmp;

	if (*begin_list && !cmp((*begin_list)->content, content_ref,
				sizeof(content_ref)))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
}

int		bfs(t_room *source, t_room *destination)
{
	t_list		*nexttov;
	t_list		*visited;

	nexttov = NULL;
	visited = NULL;
	ft_lstpushback(&nexttov, source, 0);
	ft_lstpushback(&visited, source, 0);
	(void)destination;
	while (nexttov)
	{
		if (!ft_memcmp(nexttov->content, destination, sizeof(destination)))
			return (1);
		ft_lstndump(&nexttov);
		get_children(&nexttov, &visited, nexttov->content);
		ft_lstremovefirst(&nexttov, nexttov->content, ft_memcmp);
		//ft_lstndump(&nexttov);
		/*ft_printf("VISITED \n");
		ft_lstndump(&visited);
		ft_printf("VISITED \n");*/
		//ft_lstndump(&nexttov);
		//nexttov = NULL;

		//ft_printf("child %s\n", (char*)((t_room*)tmp->content)->name);
		//ft_printf("ok\n");
		//if (--i == 0)
		//	return (0);
		//nexttov = nexttov->next;
	}
	return (0);
}

int		solver(t_list **t)
{

	t_list		*start;
	t_list		*end;

	if (!get_start_end(t, &start, &end))
		return (0);
	ft_printf("%d\n", bfs(start->content, end->content));
	//ft_printf("%d\n", ft_lstsize(((t_room*)(*start).content)->pipes));
	//ft_printf("%d\n", ft_lstsize(((t_room*)(*end).content)->pipes));
	return (1);
}
