/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:34:25 by arobion           #+#    #+#             */
/*   Updated: 2018/01/24 16:30:58 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_launch_pushback(t_room *crawler, t_room *room)
{
	/*t_room		*t;

	if (!(t = (t_room*)malloc(sizeof(t_room))))
		return ;
	ft_memcpy(t, room, sizeof(t_room));*/
	ft_lstpushback(&(crawler->pipes), room, 0);
}

int		ft_launch_cmp(t_room *crawler, const char *current_room)
{
	return (ft_strcmp(crawler->name, current_room));
}
