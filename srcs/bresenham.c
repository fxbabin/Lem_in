/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:20:53 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/01 00:13:10 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

double		ft_absdouble(double nb)
{
	return ((nb < 0.0) ? -nb : nb);
}

void		init_bresenham(t_bres *b, t_dot *d1, t_dot *d2)
{
	b->x1 = d1->x;
	b->x2 = d2->x;
	b->y1 = d1->y;
	b->y2 = d2->y;
	b->dx = b->x2 - b->x1;
	b->dy = b->y2 - b->y1;
}

void		bresenham_2(t_env *env, t_bres *b)
{
	b->delta = ft_absdouble((float)b->dx / (float)b->dy);
	b->x = b->x1;
	if (b->y2 < b->y1)
	{
		ft_swap(&b->y2, &b->y1);
		b->x = b->x2;
	}
	b->y = b->y1 - 1;
	while (++b->y <= b->y2)
	{
		mlx_pixel_put(env->mlx_ptr, env->win_ptr, b->x, b->y, 0xFFFFFF);
		b->offset += b->delta;
		if (b->offset >= b->threshold)
		{
			b->x += b->adjust;
			b->threshold += 1;
		}
	}
}

void		bresenham_1(t_env *env, t_bres *b)
{
	b->delta = ft_absdouble(b->m);
	b->y = b->y1;
	if (b->x2 < b->x1)
	{
		ft_swap(&(b->x2), &(b->x1));
		b->y = b->y2;
	}
	b->x = b->x1 - 1;
	while (++(b->x) <= b->x2)
	{
		mlx_pixel_put(env->mlx_ptr, env->win_ptr, b->x, b->y, 0xFFFFFF);
		b->offset += b->delta;
		if (b->offset >= b->threshold)
		{
			b->y += b->adjust;
			b->threshold += 1;
		}
	}
}

void		bresenham(t_env *env, t_dot *d1, t_dot *d2)
{
	t_bres			b;

	init_bresenham(&b, d1, d2);
	if (b.dx == 0)
	{
		if (b.y2 < b.y1)
			ft_swap(&b.y2, &b.y1);
		b.y = b.y1 - 1;
		while (++(b.y) <= b.y2)
			mlx_pixel_put(env->mlx_ptr, env->win_ptr, b.x1, b.y, 0xFFFFFF);
	}
	else
	{
		b.m = ((float)(b.dy) / (float)(b.dx));
		b.adjust = (b.m >= 0) ? 1 : -1;
		b.offset = 0.0;
		b.threshold = 0.5;
		if (b.m <= 1 && b.m >= -1)
			bresenham_1(env, &b);
		else
			bresenham_2(env, &b);
	}
}
