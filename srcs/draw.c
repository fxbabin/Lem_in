/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:20:36 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/01 13:41:42 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

void		draw_square(t_env *env, int x, int y, int color)
{
	int		l_x;
	int		l_y;
	int		init_x;
	int		max;

	max = ((env->screen_x - (2 * env->b_x)) / env->x) / 3;
	if ((((env->screen_y - (2 * env->b_y)) / env->y) / 3) > max)
		max = ((env->screen_y - (2 * env->b_y)) / env->y) / 3;
	max = (max > 30) ? 30 : max;
	max = (max < 1) ? 1 : max;
	l_x = x + max;
	l_y = y + max;
	x -= max;
	y -= max;
	init_x = x;
	while (x < l_x || y < l_y)
	{
		if ((x % l_x) == 0)
		{
			x = init_x;
			y++;
		}
		mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, color);
		x++;
	}
}

void		draw_l(t_env *env, t_room *r)
{
	t_dot		room;
	t_dot		pipe;
	t_list		*l;

	room.x = r->x;
	room.y = r->y;
	l = r->pipes;
	while (l)
	{
		pipe.x = (int)((t_room*)l->content)->x;
		pipe.y = (int)((t_room*)l->content)->y;
		bresenham(env, &room, &pipe);
		l = l->next;
	}
}

void		display_dots2(t_env *env, t_list **t, int *x)
{
	int			y;
	t_list		*l;

	l = *t;
	while (l)
	{
		*x = ((t_room*)l->content)->x;
		y = ((t_room*)l->content)->y;
		if (l->content_size == 0)
			draw_square(env, *x, y, 0xFFFFFF);
		else if (l->content_size == 1)
		{
			draw_square(env, *x, y, 0x354BF0);
			mlx_string_put(env->mlx_ptr, env->win_ptr, *x - 5, y - 10,
				0xFFFFFF, "S");
		}
		else if (l->content_size == 2)
		{
			draw_square(env, *x, y, 0x2BC142);
			mlx_string_put(env->mlx_ptr, env->win_ptr, *x - 5, y - 10,
				0xFFFFFF, "E");
		}
		l = l->next;
	}
}

void		display_dots(t_env *env, t_list **t)
{
	t_list		*l;
	char		*tmp;
	int			x;

	x = 0;
	l = *t;
	while (l)
	{
		draw_l(env, l->content);
		l = l->next;
	}
	l = *t;
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 50, 50, 0xFFFFFF, "Exit : Esc");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 50, 70, 0xFFFFFF, "Next : ->");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 50, 90, 0xFFFFFF, "Prev : <-");
	ft_sprintf(&tmp, "Cycle %d\n", env->step + 1);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 500, 70, 0xFFFFFF, tmp);
	free(tmp);
	display_dots2(env, t, &x);
}

void		disp_steps(t_env *env, t_list **rs, t_list **main, int step)
{
	t_room		*r;
	t_list		*l;
	t_dot		d;
	int			i;
	char		**tmp;

	l = ft_lstatpos(*rs, step);
	i = -1;
	display_dots(env, main);
	while (((char**)l->content)[++i])
	{
		tmp = ft_split(((char**)l->content)[i], "-");
		r = find_room_by_name(main, tmp[1]);
		d.x = r->x;
		d.y = r->y;
		if (r->b == 0)
		{
			draw_square(env, d.x, d.y, 0xEB402B);
			mlx_string_put(env->mlx_ptr, env->win_ptr, d.x - 5, d.y - 10,
					0x000000, tmp[0] + 1);
		}
		freechar2(tmp);
	}
}
