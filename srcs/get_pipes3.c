/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 21:08:39 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:30:57 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_verif_pipe_format(char *line)
{
	int		i;
	int		nb_sep;

	i = 0;
	nb_sep = 0;
	while (line[i] != '\0')
	{
		if (!(ft_isprint(line[i])) || line[i] == ' ')
			return (0);
		if (line[i] == '-')
			nb_sep++;
		i++;
	}
	if (nb_sep != 1)
		return (0);
	return (1);
}

int		ft_verif_unicity_of_pipe(t_room *crawler, char *name)
{
	t_list *tmp;

	tmp = crawler->pipes;
	while (tmp)
	{
		if (ft_strcmp(((t_room*)tmp->content)->name, name) == 0)
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
