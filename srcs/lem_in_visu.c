/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:40:43 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/01 14:06:54 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

t_room		*init_room(const char *str, int x, int y)
{
	t_room		*n;

	if (!(n = (t_room*)malloc(1 * sizeof(t_room))))
		return (NULL);
	n->name = ft_strdup(str);
	n->x = x;
	n->y = y;
	n->boo = 0;
	n->pipes = NULL;
	return (n);
}

int			main2(char *line, int nb_ants, t_list *t)
{
	(void)nb_ants;
	if (line == NULL)
	{
		return (0);
	}
	else if (!(get_pipes(line, &t)))
	{
		return (0);
	}
	return (1);
}

int			main3(t_list *t)
{
	t_list		*room_state;
	t_env		*env;

	set_start_end(&t);
	env = generate_map(&t);
	room_state = get_room_states();
	env->b_x = 200;
	env->b_y = 200;
	env->screen_x = 1080;
	env->screen_y = 1080;
	env->t = t;
	env->step = -1;
	env->room_state = room_state;
	env->mlx_ptr = mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->screen_x, env->screen_y,
			"LEM_IN 42 AROBION - FBABIN");
	convert_coords(env, &t);
	display_dots(env, &t);
	mlx_key_hook(env->win_ptr, deal_key, env);
	mlx_loop(env->mlx_ptr);
	return (0);
}

int			main(void)
{
	t_list		*t;
	char		*line;
	int			nb_ants;

	t = NULL;
	nb_ants = 0;
	if (!(line = get_ants(&nb_ants)))
		return (ft_printf("ERROR\n"));
	if (nb_ants == 0)
	{
		free(line);
		return (ft_printf("ERROR\n"));
	}
	line = get_rooms(line, &t);
	main2(line, nb_ants, t);
	ft_lstndump(&t);
	main3(t);
	return (0);
}
