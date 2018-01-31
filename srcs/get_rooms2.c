/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:34:35 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:31:09 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_verif_room_validity2(char **room, int i, int j)
{
	while (room[i][j] != '\0')
	{
		if (!(ft_isdigit(room[i][j])))
			return (0);
		j++;
	}
	j = 0;
	i++;
	if (room[i][0] == '-' || room[i][0] == '+')
		j = 1;
	while (room[i][j] != '\0')
	{
		if (!(ft_isdigit(room[i][j])))
			return (0);
		j++;
	}
	return (1);
}

int		ft_verif_room_validity(char **room)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (room[0][0] == 'L')
		return (0);
	while (room[i][j] != '\0')
	{
		if (!(ft_isprint(room[i][j])) || room[i][j] == '-')
			return (0);
		j++;
	}
	j = 0;
	i++;
	if (room[i][0] == '-' || room[i][0] == '+')
		j = 1;
	return (ft_verif_room_validity2(room, i, j));
}

int		ft_are_int(long long x, long long y)
{
	if (x > 2147483647 || x < -2147483648)
		return (0);
	if (y > 2147483647 || y < -2147483648)
		return (0);
	return (1);
}

int		ft_pos_cmp(t_room *crawler, long long x, long long y)
{
	if (crawler->x == x && crawler->y == y)
		return (0);
	return (1);
}

int		ft_verif_room_is_uniq(char **room, t_list **t)
{
	t_list		*crawler;
	long long	x;
	long long	y;

	x = ft_atoi_check(room[1]);
	y = ft_atoi_check(room[2]);
	if (ft_are_int(x, y) == 0)
		return (0);
	crawler = *t;
	while (crawler)
	{
		if (!(ft_launch_cmp(crawler->content, room[0])))
			return (0);
		if (!(ft_pos_cmp(crawler->content, x, y)))
			return (0);
		crawler = crawler->next;
	}
	return (1);
}
