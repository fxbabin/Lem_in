/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 21:05:23 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:29:56 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init(int *i, t_list **tmp, t_list **paths)
{
	*i = -1;
	*tmp = *paths;
}

void	ft_init2(int *j, t_list **tmp2, t_list *tmp)
{
	*j = -1;
	*tmp2 = tmp->content;
}

char	***mall_names(t_list **paths)
{
	int		i;
	int		j;
	t_list	*tmp;
	t_list	*tmp2;
	char	***names;

	ft_init(&i, &tmp, paths);
	if (!(names = (char***)malloc(sizeof(char**) * ft_lstsize(*paths))))
		return (NULL);
	while (++i < ft_lstsize(*paths))
	{
		ft_init2(&j, &tmp2, tmp);
		if (!(names[i] = (char**)malloc(sizeof(char*) *\
						(ft_lstsize(tmp->content)))))
			return (NULL);
		tmp2 = tmp2->next;
		while (++j < ft_lstsize(tmp->content) - 1)
		{
			names[i][j] = ft_strdup(((t_room*)tmp2->content)->name);
			tmp2 = tmp2->next;
		}
		names[i][j] = NULL;
		tmp = tmp->next;
	}
	return (names);
}
