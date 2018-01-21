/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:21:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/21 15:52:32 by arobion          ###   ########.fr       */
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
	return (n);
}

void	dispnode(t_room *t)
{
	ft_printf("name : %s\t; ", t->name);
	ft_printf(" x : %d\t; ", t->x);
	ft_printf("y : %d\t\t", t->y);
	ft_lstdump(&(t->sup));
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

int		ft_count_sep(char *line)
{
	int		nb_sep;
	int		i;

	nb_sep = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
			nb_sep++;
		i++;
	}
	return (nb_sep);
}

int		get_pipes(char *line, t_list **t)
{
	int		nb_sep;

	ft_printf("%s\n", line);
	t = NULL;
	if ((nb_sep = ft_count_sep(line)) == 0)
	{
		free(line);
		ft_printf("pas de '-', tube invalide\n");
		return (0);
	}
	ft_printf("nb_sep = %d\n", nb_sep);
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
	//ft_lstdump(&t);
	//ft_lstndump(&t);
	return (0);
}
