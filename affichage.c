/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:34:35 by arobion           #+#    #+#             */
/*   Updated: 2018/01/31 17:03:32 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		**mall_tabs(t_list **paths)
{
	int		i;
	t_list	*tmp;
	int		**tabs;

	i = 0;
	tmp = *paths;
	if (!(tabs = (int**)malloc(sizeof(int*) * ft_lstsize(*paths))))
		return (NULL);
	while (i < ft_lstsize(*paths))
	{
		if (!(tabs[i] = (int*)malloc(sizeof(int) *\
						(ft_lstsize(tmp->content) - 1))))
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	return (tabs);
}

void	set_tabs(t_list **paths, int **tabs)
{
	int		i;
	int		j;
	t_list	*tmp;

	tmp = *paths;
	i = 0;
	j = 0;
	while (i < ft_lstsize(*paths))
	{
		j = 0;
		while (j < ft_lstsize(tmp->content) - 1)
		{
			tabs[i][j] = 0;
			j++;
		}
		tmp = tmp->next;
		i++;
	}
}

void	affichage(t_list **paths, int *nb_ants, int nb_cycles)
{
	int		**tabs;
	int		i;
	char	***names;

	names = mall_names(paths);
	tabs = mall_tabs(paths);
	set_tabs(paths, tabs);
	i = 0;
	while (i < nb_cycles)
	{
		move_all_ants(tabs, paths);
		place_each_new_ants(tabs, paths, nb_ants, i);
		print_at_this_cycle(tabs, names, paths);
		ft_printf("\n");
		i++;
	}
	freenames(names, paths);
	freetabs(tabs, paths);
}
