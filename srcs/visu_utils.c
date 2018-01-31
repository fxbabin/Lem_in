/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:53:16 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/01 00:15:03 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_int2dumpx(int **array, int x)
{
	int		i;

	i = -1;
	if (!array || !*array)
		return ;
	while (array[++i])
	{
		ft_printf("%-4d", *array[i]);
		if (((i + 1) % (x)) == 0 && i != 0)
			ft_putstr("\n");
	}
}

t_room		*find_room_by_name(t_list **t, char *str)
{
	t_list		*l;

	l = *t;
	while (l)
	{
		if (!ft_strcmp(((t_room*)l->content)->name, str))
			return (l->content);
		l = l->next;
	}
	return (NULL);
}

void		convert_coords(t_env *env, t_list **t)
{
	t_list		*l;
	int			c_x;
	int			c_y;

	c_x = ((env->screen_x - (2 * env->b_x)) / env->x);
	c_y = ((env->screen_y - (2 * env->b_y)) / env->y);
	l = *t;
	(void)env;
	while (l)
	{
		((t_room*)l->content)->x = (((t_room*)l->content)->x * c_x) + 200;
		((t_room*)l->content)->y = (((t_room*)l->content)->y * c_y) + 200;
		l = l->next;
	}
}

void		set_start_end(t_list **t)
{
	t_list		*l;

	l = *t;
	while (l)
	{
		if (l->content_size == 1)
			((t_room*)l->content)->b = 1;
		else if (l->content_size == 2)
			((t_room*)l->content)->b = 2;
		else
			((t_room*)l->content)->b = 0;
		l = l->next;
	}
}
