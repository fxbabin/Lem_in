/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:24:14 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:48:44 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_lsttremoveif(t_list **begin_list, void *content_ref,
		int (*cmp)())
{
	t_list		*tmp;
	t_list		*curr;

	while (*begin_list && !cmp((*begin_list)->content, content_ref,
				sizeof(content_ref)))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
	curr = *begin_list;
	while (curr && curr->next)
	{
		if (!cmp((curr->next->content), content_ref, sizeof(content_ref)))
		{
			tmp = curr->next;
			curr->next = tmp->next;
			free(tmp);
		}
		if (curr->next)
			curr = curr->next;
	}
}

int			ft_is_ants(char *line)
{
	long long	nb;
	int			i;

	i = 0;
	nb = 0;
	if (line[0] == '+')
		i++;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
			return (0);
		i++;
	}
	nb = ft_atoi_check(line);
	if (nb > 2147483647)
		return (0);
	return ((int)nb);
}

char		*get_ants(int *ants)
{
	char	*line;
	int		tmp;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_putendl(line);
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if ((tmp = ft_is_ants(line)) == 0)
			return (line);
		*ants = tmp;
		if (*ants > 0)
		{
			free(line);
			get_next_line(0, &line);
			ft_printf("%s\n", line);
			return (line);
		}
	}
	free(line);
	return (NULL);
}
