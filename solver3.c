/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:55:37 by arobion           #+#    #+#             */
/*   Updated: 2018/01/31 14:49:54 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		if (!ft_lstin(visited, tmp->content, ft_memcmp, sizeof(t_room))\
				&& (int)((t_room*)tmp->content)->boo == 0)
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
