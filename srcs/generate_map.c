/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:47:19 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/01 13:34:17 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			**map_gen(t_list **t, int max_x, int max_y)
{
	t_list		*tmp;
	int			**map;

	if (!(map = ft_int2alloc((max_x * max_y), 1)))
		return (NULL);
	tmp = *t;
	while (tmp)
	{
		if (tmp->content_size == 1)
			*map[((t_room*)tmp->content)->x +
				(max_x * ((t_room*)tmp->content)->y)] = 2;
		else if (tmp->content_size == 2)
			*map[((t_room*)tmp->content)->x +
				(max_x * ((t_room*)tmp->content)->y)] = 3;
		else
			*map[((t_room*)tmp->content)->x + (max_x *
					((t_room*)tmp->content)->y)] = 1;
		tmp = tmp->next;
	}
	return (map);
}

t_env		*generate_map(t_list **t)
{
	t_list		*tmp;
	int			max_x;
	int			max_y;
	t_env		*env;

	tmp = *t;
	max_x = 0;
	max_y = 0;
	while (tmp)
	{
		if (((t_room*)tmp->content)->x > max_x)
			max_x = (int)((t_room*)tmp->content)->x;
		if (((t_room*)tmp->content)->y > max_y)
			max_y = (int)((t_room*)tmp->content)->y;
		tmp = tmp->next;
	}
	max_x++;
	max_y++;
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->x = max_x;
	env->y = max_y;
	env->coords = map_gen(t, max_x, max_y);
	return (env);
}
