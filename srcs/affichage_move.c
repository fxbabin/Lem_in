/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:57:12 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:30:15 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	move_ants_in_one_path(int *tab, int size)
{
	int		i;

	i = size - 1;
	while (i > 0)
	{
		tab[i] = tab[i - 1];
		i--;
	}
	tab[0] = 0;
}

void	move_all_ants(int **tabs, t_list **paths)
{
	int		i;
	t_list	*tmp;

	tmp = *paths;
	i = 0;
	while (i < ft_lstsize(*paths))
	{
		move_ants_in_one_path(tabs[i], ft_lstsize(tmp->content) - 1);
		i++;
		tmp = tmp->next;
	}
}
