/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:00:24 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:31:40 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		somme_sizes(int *roads_size, int nb_roads, int i, int n)
{
	int		j;
	int		result;

	j = 0;
	result = n;
	while (j < nb_roads)
	{
		if (j != i)
			result += roads_size[j];
		j++;
	}
	result = result - ((nb_roads - 1) * roads_size[i]);
	return (result);
}

void	egalize_ants(int *nb_ants, int nb_roads, int n)
{
	int		diff;
	int		i;

	diff = 0;
	i = 0;
	while (i < nb_roads)
	{
		diff += nb_ants[i];
		i++;
	}
	diff -= n;
	i = 0;
	while (diff < 0)
	{
		nb_ants[i] += 1;
		i++;
		diff++;
	}
}

void	egalize_ants2(int *nb_ants, int nb_roads, int n)
{
	int		i;
	int		j;

	(void)n;
	i = 0;
	j = 0;
	while (j < nb_roads)
	{
		i = 0;
		while (i < nb_roads)
		{
			if (nb_ants[i] < 0)
			{
				nb_ants[i - 1] = nb_ants[i - 1] + nb_ants[i];
				nb_ants[i] = 0;
				break ;
			}
			i++;
		}
		j++;
	}
}

int		how_many_ants(int *roads_size, int nb_roads, int n, t_list **paths)
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
	affichage(paths, nb_ants, ret);
	free(nb_ants);
	return (ret);
}

int		find_cycles(t_list **paths, int n)
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
	ret = how_many_ants(roads_size, nb_roads, n, paths);
	free(roads_size);
	return (ret);
}
