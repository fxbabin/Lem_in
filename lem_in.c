/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:21:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/29 20:52:46 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*init_room(const char *str, int x, int y)
{
	t_room		*n;

	if (!(n = (t_room*)malloc(1 * sizeof(t_room))))
		return (NULL);
	n->name = ft_strdup(str);
	n->x = x;
	n->y = y;
	n->boo = 0;
	n->pipes = NULL;
	return (n);
}

int			ft_is_ants(char *line)
{
	long long	nb;
	int			i;

	i = 0;
	nb = 0;
	if (line[0] == '+')
		i++;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
			return (0);
		i++;
	}
	nb = ft_atoi_check(line);
	if (nb > 2147483647)
		return (0);
	return ((int)nb);
}

char		*get_ants(int *ants)
{
	char	*line;
	int		tmp;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if ((tmp = ft_is_ants(line)) == 0)
			return (line);
		*ants = tmp;
		if (*ants > 0)
		{
			free(line);
			get_next_line(0, &line);
			ft_printf("%s\n", line);
			return (line);
		}
	}
	return (NULL);
}

void			ft_lsttremoveif(t_list **begin_list, void *content_ref,
		int (*cmp)())
{
	t_list		*tmp;
	t_list		*curr;

	while (*begin_list && !cmp((*begin_list)->content, content_ref,
				sizeof(content_ref)))
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp);
	}
	curr = *begin_list;
	while (curr && curr->next)
	{
		if (!cmp((curr->next->content), content_ref, sizeof(content_ref)))
		{
			tmp = curr->next;
			curr->next = tmp->next;
			free(tmp);
		}
		if (curr->next)
			curr = curr->next;
	}
}

int			ft_lstin(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*tmp;

	if (!begin_list || !data_ref || !cmp)
		return (0);
	tmp = *begin_list;
	while (tmp)
	{
		if (!(*cmp)(tmp->content, data_ref, sizeof(data_ref)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int			main(void)
{
	t_list	*t;
	char	*line;
	int		nb_ants;

	t = NULL;
	nb_ants = 0;
	if (!(line = get_ants(&nb_ants)))
		return (ft_printf("probleme sur les fourmis\n"));
	if (nb_ants == 0)
	{
		free(line);
		return (ft_printf("probleme sur les fourmis\n"));
	}
	line = get_rooms(line, &t);
	if (line == NULL)
	{
		ft_lstndump(&t);
		ft_printf("start_programme\n");
		ft_lstnfree(&t);
		return (0);
	}
	if (!(get_pipes(line, &t)))
	{
		ft_lstndump(&t);
		ft_printf("start programme 2\n");
		ft_lstnfree(&t);
		return (0);
	}
	ft_printf("\n");
	if (!solver(&t, nb_ants))
	{
		ft_printf("double start or double end\n");
		return (0);
	}
	ft_lstnfree(&t);
	return (0);
}
