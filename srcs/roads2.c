/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roads2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:27:20 by arobion           #+#    #+#             */
/*   Updated: 2018/01/31 17:27:53 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	affichage2(t_list **paths, int ret)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = (*paths)->content;
	tmp = tmp->next;
	while (i < ret)
	{
		ft_printf("L%d-%s\n", i + 1, ((t_room*)tmp->content)->name);
		i++;
	}
}

int		how_many_ants2(int *roads_size, int nb_roads, int n, t_list **paths)
{
	int		*nb_ants;
	int		i;
	int		ret;

	if (!(nb_ants = (int*)malloc(sizeof(int) * nb_roads + 1)))
		return (0);
	i = 0;
	while (i < nb_roads)
	{
		nb_ants[i] = (somme_sizes(roads_size, nb_roads, i, n)) / nb_roads;
		i++;
	}
	egalize_ants(nb_ants, nb_roads, n);
	egalize_ants2(nb_ants, nb_roads, n);
	ret = roads_size[0] - 2 + nb_ants[0];
	affichage2(paths, ret);
	free(nb_ants);
	return (ret);
}

int		find_cycles2(t_list **paths, int n)
{
	int			*roads_size;
	int			nb_roads;
	t_list		*tmp;
	int			i;
	int			ret;

	nb_roads = ft_lstsize(*paths);
	if (!(roads_size = malloc(sizeof(int) * nb_roads)))
		return (0);
	tmp = *paths;
	i = 0;
	while (i < nb_roads)
	{
		roads_size[i] = ft_lstsize(tmp->content);
		tmp = tmp->next;
		i++;
	}
	ret = how_many_ants2(roads_size, nb_roads, n, paths);
	free(roads_size);
	return (ret);
}
