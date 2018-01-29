/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:18:53 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/29 15:21:21 by arobion          ###   ########.fr       */
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

void		ft_lstpushlist(t_list **begin_list, t_list **add, int (*cmp)(), size_t size)
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

void	ft_lstremovedoubles(t_list **t)
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

void	get_children(t_list **t, t_list **visited, t_room *room)
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

int		new_bfs(t_list **ntv, t_list **visited, t_room *dest)
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

t_list		*find_path(t_list **visited, t_list *end, t_list *start)
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

void	ft_change_boo(t_list *path)
{
	t_list	*tmp;

	tmp = path->next;
	while (tmp->next)
	{
		((t_room*)tmp->content)->boo = 1;
		tmp = tmp->next;
	}
}

void	ft_launch_dump(t_list *list)
{
	ft_lstndump(&list);
}

t_list	*one_son(t_list *ntv, t_list *visited, t_list *end, t_list *start_pipes, t_list *start)
{
	t_list	*path;

	new_bfs(&ntv, &visited, end->content);
	path = find_path(&visited, end, start_pipes);
	ft_lstpushfront(&path, start->content, 0);
	ft_change_boo(path);
	return (path);
}


int		launcher(t_list *start_pipes, t_list *end, t_list *ntv, int nb_ants, t_list *start)
{
	t_list	*visited;
	t_list	*paths_list;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*path;

	visited = NULL;
	paths_list = NULL;
	tmp = start_pipes;
	tmp2 = ((t_room*)start_pipes->content)->pipes;
	ft_printf("name next = %s\n", ((t_room*)start_pipes->next->content)->name);
	while (tmp2)
	{
		if (((t_room*)tmp2->content)->boo == 0)
		{
			ft_lstpushback(&ntv, tmp2->content, 0);
			break ;
		}
		ft_printf("name = %s | ", ((t_room*)tmp2->content)->name);
		ft_printf("boo = %d\n", ((t_room*)tmp2->content)->boo);
		tmp2 = tmp2->next;
	}
	path = one_son(ntv, visited, end, start_pipes->next, start);	
	ft_lstpushback(&paths_list, path, 0);
//	path = one_son(ntv, visited, end, start_pipes->next, start);
//	ft_lstpushback(&paths_list, path, 0);
	ft_lstndump(&path);
	ft_lstpushback(&ntv, start_pipes->content, 0);
	return (find_cycles(&paths_list, nb_ants));
}

t_list	*test1(t_list *ntv, t_list *start, t_list *end, t_list *visited)
{
	ft_lstpushback(&ntv, start->content, 0);
	new_bfs(&ntv, &visited, end->content);
	return (find_path(&visited, end, start));
}

t_list	*back1(t_list *ntv, t_list *start, t_list *end, t_list *visited, t_list *fils)
{
	t_list	*path;
	t_list	*paths_list;

	paths_list = NULL;
	(void)fils;
	(void)start;
	while (fils)
	{
		path = test1(ntv, fils, end, visited);	
		ft_lstpushfront(&path, start->content, 0);
		ft_lstpushback(&paths_list, path, 0);
		ft_change_boo(path);
		fils = fils->next;
		ft_lstndump(&path);
	}
	return (paths_list);
}

int		solver(t_list **t, int nb_ants)
{
	t_list		*ntv;
	t_list		*start;
	t_list		*end;
	t_list		*fils;

	t_list		*visited;
	t_list		*paths;
	int			i;

	ntv = NULL;

	visited = NULL;
	(void)i;
	(void)nb_ants;
	if (!get_start_end(t, &start, &end))
		return (0);
	//ft_lstpushback(&ntv, start->content, 0);
	((t_room*)start->content)->boo = 1;
	fils = ((t_room*)start->content)->pipes;
	paths = back1(ntv, start, end, visited, start);
	i = find_cycles(&paths, nb_ants);
	ft_printf("nb_cycles = %d\n", i);









	//i = launcher((t_list*)((t_room*)start->content)->pipes, end, ntv, nb_ants, start);
	//launcher(start, end, ntv, nb_ants, start);
	//ft_printf("nb_cycles = %d\n", i);
//	while (paths_list)
//	{
//		ft_launch_dump(paths_list->content);
//		paths_list = paths_list->next;
//	}
	/*
	ft_printf("%d\n", new_bfs(&ntv, &visited, end->content));
	//ft_printf("VISITED\n");
	//ft_lstndump(&visited);
	//ft_printf("VISITED\n");
	//ft_lstndump(&ntv);
	//ft_printf("%s\n", ((t_room*)(*start).content)->name);
	//	ft_printf("%s\n", ((t_room*)(*end).content)->name);
	//	ft_printf("\n\n");
	path = find_path(&visited, end, start);
	ft_lstndump(&path);
	ft_change_boo(path);
	ntv = NULL;
	visited = NULL;
	ft_lstpushback(&ntv, start->content, 0);
	ft_printf("%d\n", new_bfs(&ntv, &visited, end->content));
	path = find_path(&visited, end, start);
	ft_lstndump(&path);
	*/
	return (1);
}
