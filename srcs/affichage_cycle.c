/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 20:54:18 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:30:05 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print(int nb, char *str)
{
	if (nb != 0)
		ft_printf("L%d-%s ", nb, str);
}

void	print_one_path(int *tab, char **names, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		print(tab[i], names[i]);
		i++;
	}
}

void	print_at_this_cycle(int **tabs, char ***names, t_list **paths)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *paths;
	while (i < ft_lstsize(*paths))
	{
		print_one_path(tabs[i], names[i], ft_lstsize(tmp->content) - 1);
		i++;
		tmp = tmp->next;
	}
}
