/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room_states.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:38:25 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/31 16:40:37 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			**get_words(char **tab)
{
	char	**out;
	int		i;

	i = -1;
	while (tab[++i])
		;
	if (!(out = (char**)ft_memalloc((i + 1) * sizeof(char*))))
		return (NULL);
	i = -1;
	while (tab[++i])
		out[i] = ft_strdup(tab[i]);
	return (out);
}

t_list			*get_room_states(void)
{
	char		*line;
	char		**tab;
	t_list		*all;
	char		**t;

	all = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!line[0])
			ft_printf("LIGNE VIDE\n");
		else
		{
			tab = ft_split(line, " ");
			ft_char2dump(tab);
			t = get_words(tab);
			ft_lstpushback(&all, t, 0);
			ft_free2((void**)tab);
		}
		free(line);
	}
	free(line);
	return (all);
}
