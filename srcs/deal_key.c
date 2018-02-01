/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:08:45 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/01 14:01:34 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

void			go_forward(t_env *env)
{
	t_list		*l;
	t_list		*rs;
	int			size;

	l = env->t;
	rs = env->room_state;
	size = ft_lstsize(rs);
	if (env->step == -1)
	{
		env->step += 1;
		disp_steps(env, &rs, &l, env->step);
	}
	else if (env->step == size - 2)
		display_dots(env, &l);
	else
	{
		env->step += 1;
		if (env->step < size)
			disp_steps(env, &rs, &l, env->step);
	}
}

void			go_backward(t_env *env)
{
	t_list		*l;
	t_list		*rs;
	int			size;

	l = env->t;
	rs = env->room_state;
	size = ft_lstsize(rs);
	if (env->step == -1)
		display_dots(env, &l);
	else if (env->step == size)
	{
		display_dots(env, &l);
		env->step -= 1;
	}
	else
	{
		if (env->step > -1)
			disp_steps(env, &rs, &l, env->step);
		env->step -= 1;
	}
}

void			free_rs(t_list *rs)
{
	t_list		*l;
	t_list		*tmp;

	l = rs;
	while (l)
	{
		tmp = l->next;
		freechar2(l->content);
		free(l);
		l = tmp;
	}
}

void			free_env(t_env *env)
{
	int		i;

	i = -1;
	while (((int**)env->coords)[++i])
		;
	while (i > 0)
		free(((int**)env->coords)[--i]);
	free(((int**)env->coords));
	free_rs(env->room_state);
	ft_lstnfree(&env->t);
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	free(env);
}

int				deal_key(int key, void *param)
{
	t_env		*env;

	env = (t_env*)param;
	if (key == 53)
	{
		ft_printf("EXIT VISUALISOR\n");
		free_env(env);
		exit(0);
	}
	else if (key == 124)
		go_forward(env);
	else if (key == 123)
		go_backward(env);
	return (0);
}
