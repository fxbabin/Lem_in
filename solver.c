/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:18:53 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/29 18:57:16 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				get_start_end(t_list **list, t_list **start, t_list **end)
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

static int		ft_lstin(t_list **begin_list, void *data_ref, int (*cmp)(),
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

void			ft_lstremovefirst(t_list **begin_list, void *content_ref,
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

void			ft_lstpushlist(t_list **begin_list, t_list **add, int (*cmp)(), size_t size)
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

void			ft_lstremovedoubles(t_list **t)
{
	t_list		*uniq;
	t_list		*tmp;

	uniq = NULL;
	tmp = *t;
	while (tmp)
	{
		if (!ft_lstin(&uniq, tmp->content, ft_memcmp, sizeof(t_room)))
			ft_lstpushback(&uniq, tmp->content, 0);
		tmp = tmp->next;
	}
	ft_lstdel(t, ft_eldel);
	*t = uniq;
}

void			get_children(t_list **t, t_list **visited, t_room *room)
{
	t_list		*tmp;

	tmp = room->pipes;
	while (tmp)
	{
		if (!ft_lstin(visited, tmp->content, ft_memcmp, sizeof(t_room)) && (int)((t_room*)tmp->content)->boo == 0)
			ft_lstpushback(t, (t_room*)tmp->content, 0);
		tmp = tmp->next;
	}
}

int				new_bfs(t_list **ntv, t_list **visited, t_room *dest)
{
	int		ret;
	int		n;

	if (!(*ntv))
		return (0);
	if (ft_lstin(ntv, dest, ft_memcmp, sizeof(t_room)))
		return (1);
	else
	{
		ft_lstpushlist(visited, ntv, ft_memcmp, sizeof(t_room));
		n = ft_lstsize(*ntv);
		while (n--)
		{
			get_children(ntv, visited, (*ntv)->content);
			ft_lstremovefirst(ntv, (*ntv)->content, ft_memcmp, sizeof(t_room));
		}
		ft_lstremovedoubles(ntv);
		ret = new_bfs(ntv, visited, dest);
		if (ret)
			return (1);
	}
	return (0);
}

t_list			*find_path(t_list **visited, t_list *end, t_list *start)
{
	t_list		*tmpv;
	t_list		*ret;
	t_list		*curr;

	curr = end;
	ret = NULL;
	ft_lstpushfront(&ret, end->content, 0);
	tmpv = *visited;
	while (tmpv && ft_memcmp(curr, start, sizeof(t_list*)))
	{
		if (ft_lstin(&((t_room*)curr->content)->pipes, tmpv->content, ft_memcmp, sizeof(t_room)))
		{
			ft_lstpushfront(&ret, tmpv->content, 0);
			curr = tmpv;
			tmpv = *visited;
			continue ; 
		}
		tmpv = tmpv->next;
	}
	return (ret);	
}

void			ft_change_boo(t_list *path)
{
	t_list	*tmp;

	tmp = path->next;
	while (tmp->next)
	{
		((t_room*)tmp->content)->boo = 1;
		tmp = tmp->next;
	}
}

void			ft_launch_dump(t_list *list)
{
	ft_lstndump(&list);
}

int				solver(t_list **t, int nb_ants)
{
	t_list		*ntv;
	t_list		*visited;
	t_list		*start;
	t_list		*end;
	t_list		*path;
	t_list		*paths_list;

	ntv = NULL;
	visited = NULL;
	paths_list = NULL;
	if (!get_start_end(t, &start, &end))
		return (0);
	ft_lstpushback(&ntv, start->content, 0);
	while (new_bfs(&ntv, &visited, end->content))
	{
		path = find_path(&visited, end, start);
		ft_lstpushback(&paths_list, path, 0);
		ft_change_boo(path);
//		ft_lstnfree2(&path);
		ntv = NULL;
		visited = NULL;
		ft_lstpushback(&ntv, start->content, 0);
	}
	find_cycles(&paths_list, nb_ants);
//	ft_lstnfree(&paths_list);
	return (1);
}
