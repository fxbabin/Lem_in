/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:20:53 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/31 20:56:24 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "mlx.h"

double		ft_absdouble(double nb)
{
	return ((nb < 0.0) ? -nb : nb);
}

void	bresenham(t_env *env, int x1, int y1, int x2, int y2)
{
	int             dx;
	int             dy;
	float   m;
	int             adjust;
	float   offset;
	float   threshold;
	float   delta;
	int             x;
	int             y;

	dx = x2 - x1;
	dy = y2 - y1;
	if (dx == 0)
	{
		if (y2 < y1)
			ft_swap(&y2, &y1);
		y = y1 - 1;
		while (++y <= y2)
			mlx_pixel_put(env->mlx_ptr, env->win_ptr, x1, y, 0xFFFFFF);
	}
	else
	{
		m = ((float)dy / (float)dx);
		adjust= (m >= 0) ? 1 : -1;
		offset = 0.0;
		threshold = 0.5;
		if (m <= 1 && m >= -1)
		{
			delta = ft_absdouble(m);
			y = y1;
			if (x2 < x1)
			{
				ft_swap(&x2, &x1);
				y = y2;
			}
			x = x1 - 1;
			while (++x <= x2)
			{
				mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, 0xFFFFFF);
				offset += delta;
				if (offset >= threshold)
				{
					y += adjust;
					threshold += 1;
				}
			}
		}
		else
		{
			delta = ft_absdouble((float)dx / (float)dy);
			x = x1;
			if (y2 < y1)
			{
				ft_swap(&y2, &y1);
				x = x2;
			}
			y = y1 - 1;
			while (++y <= y2)
			{
				mlx_pixel_put(env->mlx_ptr, env->win_ptr, x, y, 0xFFFFFF);
				offset += delta;
				if (offset >= threshold)
				{
					x += adjust;
					threshold += 1;
				}
			}
		}
	}
}

/*void		bresenham_2(t_env *env, t_bres *b, t_dot *d1, t_dot *d2)
{
	b->delta = ft_absdouble((float)b->dx / (float)b->dy);
	b->x = d1->x;
	if (d2->y < d1->y)
	{
		ft_swap(&(d2->y), &(d1->y));
		b->x = d2->x;
	}
	b->y = d1->y - 1;
	while (++(b->y) <= d2->y)
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

void	bresenham_1(t_env *env, t_bres *b, t_dot *d1, t_dot *d2)
{
	b->delta = ft_absdouble(b->m);
	b->y = d1->y;
	if (d2->x < d1->x)
	{
		ft_swap(&(d2->x), &(d1->x));
		b->y = d2->y;
	}
	b->x = d1->x - 1;
	while (++(b->x) <= d2->x)
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

void    bresenham(t_env *env, t_dot *d1, t_dot *d2)
{
	t_bres		b;

	b.dx = d2->x - d1->x;
	b.dy = d2->y - d1->y;
	if (b.dx == 0)
	{
		if (d2->y < d1->y)
			ft_swap(&(d2->y), &(d1->y));
		b.y = (d1->y) - 1;
		while (++(b.y) <= d2->y)
			mlx_pixel_put(env->mlx_ptr, env->win_ptr, d1->x, b.y, 0xFFFFFF);
	}
	else
	{
		b.m = ((float)(b.dy) / (float)(b.dx));
		b.adjust= (b.m >= 0) ? 1 : -1;
		b.offset = 0.0;
		b.threshold = 0.5;
		if (b.m <= 1 && b.m >= -1)
			bresenham_1(env, &b, d1, d2);
		else
			bresenham_2(env, &b, d1, d2);
	}
}*/
