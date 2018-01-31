/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:33:11 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:30:48 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*get_room_by_name(t_list **t, char *name)
{
	t_list		*l;

	l = *t;
	while (l)
	{
		if (ft_launch_cmp(l->content, name) == 0)
			return (l->content);
		l = l->next;
	}
	return (NULL);
}

int		ft_add_pipes_to_room(t_list **t, char *name1, char *name2)
{
	t_list	*crawler;

	crawler = *t;
	while (crawler)
	{
		if (ft_launch_cmp(crawler->content, name1) == 0)
		{
			if (ft_verif_unicity_of_pipe(crawler->content, name2) == 0)
				return (0);
			ft_launch_pushback(crawler->content, get_room_by_name(t, name2));
		}
		if (ft_launch_cmp(crawler->content, name2) == 0)
			ft_launch_pushback(crawler->content, get_room_by_name(t, name1));
		crawler = crawler->next;
	}
	return (1);
}

int		get_pipes2(char *line, t_list **t, int i)
{
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		i = 0;
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if (!(ft_verif_pipe_format(line)))
		{
			free(line);
			return (0);
		}
		while (line[i] != '-')
			i++;
		if (!(ft_are_rooms_exists(line, i, t)))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	free(line);
	return (1);
}

int		get_pipes(char *line, t_list **t)
{
	int		i;

	i = 0;
	if (!(ft_verif_pipe_format(line)))
	{
		free(line);
		return (0);
	}
	while (line[i] != '-')
		i++;
	if (!(ft_are_rooms_exists(line, i, t)))
	{
		free(line);
		return (0);
	}
	free(line);
	return (get_pipes2(line, t, i));
}
