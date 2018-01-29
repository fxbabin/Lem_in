/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:34:35 by arobion           #+#    #+#             */
/*   Updated: 2018/01/29 15:28:58 by arobion          ###   ########.fr       */
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

void	affichage(t_list **paths, int *nb_ants, int n, int nb_cycles)
{
	int		**tabs;
	int		i;
	char	***names;
	t_list	*tmp;
	int		j;
	t_list	*tmp2;

	(void)nb_ants;
	(void)n;
	tmp = *paths;
	i = 0;
	if (!(tabs = (int**)malloc(sizeof(int*) * ft_lstsize(*paths))))
		return ;
	if (!(names = (char***)malloc(sizeof(char**) * ft_lstsize(*paths))))
		return ;
	while (i < ft_lstsize(*paths))
	{
		j = 0;
		tmp2 = tmp->content;
		if (!(tabs[i] = (int*)malloc(sizeof(int) * (ft_lstsize(tmp->content) - 1))))
			return ;
		if (!(names[i] = (char**)malloc(sizeof(char*) * (ft_lstsize(tmp->content) - 1))))
			return ;
		tmp2 = tmp2->next;
		while (j < ft_lstsize(tmp->content) - 1)
		{
			names[i][j] = ft_strdup(((t_room*)tmp2->content)->name);
			tmp2 = tmp2->next;
			j++;
		}
		i++;
		tmp = tmp->next;
	}
/*	i = 0;
	j = 0;
	tmp = *paths;
	while (i < ft_lstsize(*paths))
	{
		j = 0;
		while (j < ft_lstsize(tmp->content))
		{
			ft_printf("name[%d][%d] = %s\n", i, j, names[i][j]);
			j++;
		}
		tmp = tmp->next;
		i++;
	}
*/
	i = 0;
	j = 0;
	while (i < nb_cycles)
	{
		move_all_ants(tabs, paths);
		place_each_new_ants(tabs, paths, nb_ants, i);
		print_at_this_cycle(tabs, names, paths);
		ft_printf("\n");
		i++;
	}
}
