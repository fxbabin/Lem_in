/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:42:56 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:31:04 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_rooms_norme1(char **line, int *b)
{
	if (!ft_strcmp(*line, "##start"))
	{
		free(*line);
		*b = 1;
		get_next_line(0, line);
		ft_printf("%s\n", *line);
		get_rooms_norme1(line, b);
	}
	else if (!ft_strcmp(*line, "##end"))
	{
		free(*line);
		*b = 2;
		get_next_line(0, line);
		ft_printf("%s\n", *line);
		get_rooms_norme1(line, b);
	}
}

void	ft_push(t_list **t, char **room, int b)
{
	ft_lstpushback(t, init_room(room[0],\
				ft_atoi(room[1]), ft_atoi(room[2])), b);
}

char	*get_rooms2(char *line, t_list **t, char **room, int b)
{
	while (get_next_line(0, &line) > 0)
	{
		print_and_norme(line, &b);
		if (line[0] == '#')
			get_rooms_norme1(&line, &b);
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if (!(room = ft_verif_room_format(line)))
			return (line);
		if (!(ft_verif_room_validity(room)))
		{
			freechar2(room);
			return (line);
		}
		if (!(ft_verif_room_is_uniq(room, t)))
		{
			freechar2(room);
			free(line);
			return (NULL);
		}
		ft_push(t, room, b);
		freechar2(room);
		free(line);
	}
	return (line);
}

int		get_rooms3(char *line, char **room, t_list **t, int b)
{
	if (!(room = ft_verif_room_format(line)))
		return (1);
	if (!(ft_verif_room_validity(room)))
	{
		freechar2(room);
		return (1);
	}
	if (!(ft_verif_room_is_uniq(room, t)))
	{
		freechar2(room);
		free(line);
		return (0);
	}
	ft_lstpushback(t, init_room(room[0],\
				ft_atoi(room[1]), ft_atoi(room[2])), b);
	freechar2(room);
	free(line);
	return (2);
}

char	*get_rooms(char *line, t_list **t)
{
	char	**room;
	int		b;
	int		tril;

	(void)t;
	b = 0;
	room = NULL;
	if (line[0] == '#')
		get_rooms_norme1(&line, &b);
	if (ft_verif_line_is_comm(line) == 0)
	{
		tril = get_rooms3(line, room, t, b);
		if (tril == 0)
			return (NULL);
		else if (tril == 1)
			return (line);
	}
	return (get_rooms2(line, t, room, b));
}
