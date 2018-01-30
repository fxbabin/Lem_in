/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage_first_ants.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:59:38 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:30:10 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		min_path(int *nb_ants, int i)
{
	int		ret;
	int		j;

	j = 0;
	ret = 0;
	while (j < i)
	{
		ret += nb_ants[j];
		j++;
	}
	return (ret);
}

int		max_path(int *nb_ants, int i)
{
	int		ret;
	int		j;

	j = 0;
	ret = 0;
	while (j <= i)
	{
		ret += nb_ants[j];
		j++;
	}
	return (ret);
}

void	place_new_ants_in_one_path(int *tab, int *nb_ants, int i, int n_c)
{
	int		j;

	j = tab[1];
	if (j == 0)
	{
		if (n_c == 0)
			j = min_path(nb_ants, i);
		else
			j = -1;
	}
	if (j >= max_path(nb_ants, i))
		j = -1;
	tab[0] = j + 1;
}

void	place_each_new_ants(int **tabs, t_list **paths, int *nb_ants, int n_c)
{
	int		i;
	t_list	*tmp;

	tmp = *paths;
	i = 0;
	while (i < ft_lstsize(*paths))
	{
		place_new_ants_in_one_path(tabs[i], nb_ants, i, n_c);
		i++;
		tmp = tmp->next;
	}
}
