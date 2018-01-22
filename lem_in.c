/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:21:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/22 18:27:34 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	freechar2(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);

}

t_room		*init_room(const char *str, int x, int y)
{
	t_room		*n;

	if (!(n = (t_room*)malloc(1 * sizeof(t_room))))
		return (NULL);
	n->name = ft_strdup(str);
	n->x = x;
	n->y = y;
	n->sup = NULL;
	n->pipes = NULL;
	return (n);
}

void	dispnode(t_room *t)
{
	ft_printf("name : %s\t; ", t->name);
	ft_printf(" x : %d\t; ", t->x);
	ft_printf("y : %d\t\t", t->y);
	ft_lstdump(&(t->pipes));
}

void		ft_lstndump(t_list **list)
{
	t_list		*l;

	if (!list || !*list)
	{
		ft_putstr("(null)\n");
		return ;
	}
	l = *list;
	while ((*list))
	{
		if ((*list)->content)
			dispnode((*list)->content);
		else
			ft_putstr(" (null) ");
		//ft_putstr(";\tcs[");
		//ft_putnbr((*list)->content_size);
		//ft_putstr("]\t");
		//ft_putstr(" -> ");
		*list = (*list)->next;
	}
	ft_putstr("NULL\n");
	*list = l;
}
/*int		is_comment(const char *line)
  {
  if (ft_strcmp(line, "##end") && *line == '#')
  return (1);
  return (0);
  }*/
/*void	treat_line(t_list **t, )
  {


  }*/

int		numelems(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

int		ft_checknode(char **tab)
{
	int		i;

	i = -1;
	while (tab[0][++i])
	{
		if (!ft_isalnum(tab[0][i]))
			return (0);
	}
	i = 0;
	while (++i < 3)
	{
		if (!ft_strbspn(tab[i], "-0123456789"))
			return (0);
	}
	return (1);
}

int		ft_checkpath(char **tab)
{
	int		i;
	int		y;

	i = -1;
	while (++i < 2)
	{
		y = -1; 
		if (!ft_isalnum(tab[i][++y]))
			return (0);
	}
	return (1);
}

int		ft_is_ants(char *line)
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

char	*get_ants(int *ants)
{
	char	*line;
	int		tmp;
	
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if ((tmp = ft_is_ants(line)) == 0)
			return (line);
		*ants = tmp;
		if (*ants > 0)
		{
			free(line);
			get_next_line(0, &line);
			return (line);
		}
	}
	return (NULL);
}

void	ft_eldel(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}

void	ft_free_pipes(t_list **pipes)
{
	t_list *tmp;
	t_list *tmp2;

	tmp = *pipes;
	if (!tmp)
		return ;
	while (tmp->next)
	{
//		ft_free_test(tmp->content);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
//	ft_free_test(tmp->content);
	free(tmp);
}

void	ft_free_rooms(t_room *room)
{
	ft_free_pipes(&(room->pipes));
	free(room->sup);
	free((void*)room->name);
}

void	ft_free_listception(t_list **t)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *t;
	while (tmp->next)
	{
		ft_free_rooms(tmp->content);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	ft_free_rooms(tmp->content);
	free(tmp);
}

int		main(void)
{
	t_list	*t;
	char	*line;
	int		nb_ants;

	
	t = NULL;
	nb_ants = 0;
	if(!(line = get_ants(&nb_ants)))
		return (ft_printf("probleme sur les fourmis\n"));
	if (nb_ants == 0)
		return (ft_printf("probleme sur les fourmis\n"));
	line = get_rooms(line, &t);
	if (line == NULL)
		return (ft_printf("start_programme\n"));
	if (!(get_pipes(line, &t)))
		return (ft_printf("start programme 2\n"));
	ft_printf("start programme 3\n");
	ft_free_listception(&t);
	//ft_lstdump(&t);
//	ft_lstndump(&t);
	return (0);
}
