/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:21:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/22 12:23:51 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

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

int		ft_verif_pipe_format(char *line)
{
	int		i;
	int		nb_sep;

	i = 0;
	nb_sep = 0;
	while (line[i] != '\0')
	{
		if (!(ft_isprint(line[i])) || line[i] == ' ')
			return (0);
		if (line[i] == '-')
			nb_sep++;
		i++;
	}
	if (nb_sep != 1)
		return (0);
	return (1);
}

void	ft_launch_pushback(t_room *crawler, char *name)
{
	ft_lstpushback(&(crawler->pipes), name, 0);
}

int		ft_add_pipes_to_room(t_list **t, char *name1, char *name2)
{
	t_list	*crawler;

	crawler = *t;
	while (crawler)
	{
		if (ft_launch_cmp(crawler->content, name1) == 0)
			ft_launch_pushback(crawler->content, name2);
		if (ft_launch_cmp(crawler->content, name2) == 0)
			ft_launch_pushback(crawler->content, name1);
		crawler = crawler->next;
	}
	return (1);
}

int		ft_search_rooms_name(char *name1, char *name2, t_list **t)
{
	int		i;
	int		j;
	t_list	*crawler;

	if (ft_strcmp(name1, name2) == 0)
		return (0);
	i = 0;
	j = 0;
	crawler = *t;
	while (crawler)
	{
		if (ft_launch_cmp(crawler->content, name1) == 0)
			i = 1;
		crawler = crawler->next;
	}
	crawler = *t;
	while (crawler)
	{
		if (ft_launch_cmp(crawler->content, name2) == 0)
			j = 1;
		crawler = crawler->next;
	}
	if (i == 1 && j == 1)
	{
		if (!(ft_add_pipes_to_room(t, name1, name2)))
			return (0);
		return (1);
	}
	return (0);
}

int		ft_are_rooms_exists(char *line, int i, t_list **t)
{
	int		j;
	char	*name1;
	char	*name2;

	j = 0;
	if (!(name1 = (char*)malloc(sizeof(char) * i)))
		return (0);
	while (j < i)
	{
		name1[j] = line[j];
		j++;
	}
	name1[j] = '\0';
	j = i + 1;
	while (line[j] != '\0')
		j++;
	if (!(name2 = (char*)malloc(sizeof(char) * (j - i))))
		return (0);
	j = 0;
	i++;
	while (line[i] != '\0')
	{
		name2[j] = line[i];
		j++;
		i++;
	}
	name2[j] = '\0';
	if (!(ft_search_rooms_name(name1, name2, t)))
		return (0);
	return (1);
}

int		get_pipes(char *line, t_list **t)
{
	int		i;

	i = 0;
	if (!(ft_verif_pipe_format(line)))
		return (0);
	while (line[i] != '-')
		i++;
	if (!(ft_are_rooms_exists(line, i, t)))
		return (0);
	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if (!(ft_verif_pipe_format(line)))
			return (0);
		while (line[i] != '-')
			i++;
		if (!(ft_are_rooms_exists(line, i, t)))
			return (0);
		ft_printf("line = %s\n", line);
	}
	return (1);
}

int		main(void)
{
	t_list	*t;
	char	*line;

	t = NULL;
	line = get_rooms(&t);
	if (line == NULL)
		return (ft_printf("start_programme\n"));
	if (!(get_pipes(line, &t)))
		return (ft_printf("start programme 2\n"));
	ft_printf("start programme 3\n");
	//ft_lstdump(&t);
//	ft_lstndump(&t);
	return (0);
}
