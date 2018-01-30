/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:30:39 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:30:53 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_boucle_norme(t_list **crawler, char *name, int *i)
{
	if (ft_launch_cmp((*crawler)->content, name) == 0)
		*i = 1;
	*crawler = (*crawler)->next;
}

int		ft_search_rooms_name(char *name1, char *name2, t_list **t)
{
	int		i;
	int		j;
	t_list	*crawler;

	if (ft_strcmp(name1, name2) == 0)
		return (0);
	i = 0;
	j = 0;
	crawler = *t;
	while (crawler)
		ft_boucle_norme(&crawler, name1, &i);
	crawler = *t;
	while (crawler)
		ft_boucle_norme(&crawler, name2, &j);
	if (i == 1 && j == 1)
	{
		if (!(ft_add_pipes_to_room(t, name1, name2)))
			return (0);
		return (1);
	}
	return (0);
}

void	ft_cop1(char *name1, char *line, int j, int i)
{
	while (j < i)
	{
		name1[j] = line[j];
		j++;
	}
	name1[j] = '\0';
}

void	ft_cop2(char *name2, char *line, int j, int i)
{
	while (line[i] != '\0')
	{
		name2[j] = line[i];
		j++;
		i++;
	}
	name2[j] = '\0';
}

int		ft_are_rooms_exists(char *line, int i, t_list **t)
{
	int		j;
	char	*name1;
	char	*name2;

	j = 0;
	if (!(name1 = (char*)malloc(sizeof(char) * i + 1)))
		return (0);
	ft_cop1(name1, line, j, i);
	j = i + 1;
	while (line[j] != '\0')
		j++;
	if (!(name2 = (char*)malloc(sizeof(char) * (j - i))))
		return (0);
	j = 0;
	i++;
	ft_cop2(name2, line, j, i);
	if (!(ft_search_rooms_name(name1, name2, t)))
	{
		free(name1);
		free(name2);
		return (0);
	}
	free(name1);
	free(name2);
	return (1);
}
