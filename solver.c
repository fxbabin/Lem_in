/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:18:53 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/30 15:56:50 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		if (ft_lstin(&((t_room*)curr->content)->pipes,\
					tmpv->content, ft_memcmp, sizeof(t_room)))
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

void			print_paths(t_list **paths)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;
	int		j;

	i = -1;
	tmp = *paths;
	ft_printf("-------------------------------------\n\n");
	while (++i < ft_lstsize(*paths))
	{
		tmp2 = tmp->content;
		j = -1;
		ft_printf("chemin %d:\n", i + 1);
		while (++j < ft_lstsize(tmp->content) - 1)
		{
			ft_printf("%s ==> ", ((t_room*)tmp2->content)->name);
			tmp2 = tmp2->next;
		}
		ft_printf("%s", ((t_room*)tmp2->content)->name);
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("\n-------------------------------------\n\n");
}

int				solver(t_list **t, int nb_ants, int option)
{
	t_list		*ntv;
	t_list		*visited;
	t_list		*start;
	t_list		*end;
	t_list		*path;
	t_list		*paths_list;
	int			i;

	ft_printf("\n");
	i = 0;
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
		ntv = NULL;
		visited = NULL;
		ft_lstpushback(&ntv, start->content, 0);
		i++;
	}
	if (i == 0)
		return (0);
	if (option == 1)
		print_paths(&paths_list);
	find_cycles(&paths_list, nb_ants);
	return (1);
}
