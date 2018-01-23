/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:34:25 by arobion           #+#    #+#             */
/*   Updated: 2018/01/23 12:33:47 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_launch_pushback(t_room *crawler, char *name)
{
	ft_lstpushback(&(crawler->pipes), ft_strdup(name), 0);
}

int		ft_launch_cmp(t_room *crawler, const char *current_room)
{
	return (ft_strcmp(crawler->name, current_room));
}
