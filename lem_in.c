/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:21:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/19 18:17:05 by fbabin           ###   ########.fr       */
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

t_node		*init_node(const char *str, int x, int y)
{
	t_node		*n;

	if (!(n = (t_node*)malloc(1 * sizeof(t_node))))
		return (NULL);
	n->name = ft_strdup(str);
	n->x = x;
	n->y = y;
	n->sup = NULL;
	return (n);
}

void	dispnode(t_node *t)
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

t_list		*get_nodebyname(t_list **t)
{
	

}


/*  CHECK DOUBLE ROOMS */

void	get_rooms(t_list **t)
{
	char	*line;
	char	**tab;
	int		n;
	int		b;

	line = NULL;
	(void)t;
	//b = 0;
	while (get_next_line(0, &line) > 0)
	{
		b = 0;
		if (line[0] == '#')
		{
			if (!ft_strcmp(line, "##start"))
			{
				free(line);
				get_next_line(0, &line);
				b = 1;
			}
			else if (!ft_strcmp(line, "##end"))
			{
				free(line);
				get_next_line(0, &line);
				b = 2;
			}
			else
			{
				free(line);
				get_next_line(0, &line);
			}
		}
		if (ft_charinset('-', line) && !ft_charinset(' ', line)) //ft_isalnum(line[ft_strlen(line) - 1]))
			tab = ft_split(line, "-");
		else if (ft_charinset(' ', line)) //ft_isalnum(line[ft_strlen(line) - 1]))
			tab = ft_split(line, " ");
		else
			break ;
		ft_char2dump(tab);
		n = numelems(tab);
		if (n == 3)
		{
			if (!ft_checknode(tab))
				break ;
			ft_lstpushback(t, init_node(tab[0], ft_atoi(tab[1]), ft_atoi(tab[2])), b);
		}
		if (n == 2)
		{
			if (!ft_checkpath(tab))
				break ;

		}
		/*else
			error*/
			//ft_lstpushback(t, init_node(tab[0],), 0);

		//if (!ft_strcmp(line, "##start"))
		//	break ;

		//ft_lstdump(t);
		//ft_char2dump(tab);
		//freechar2(tab);
		ft_printf("%s\n", line);
		free(line);
	}
	free(line);
}

int		main(void)
{
	t_list	*t;

	t = NULL;
	get_rooms(&t);
	//ft_lstdump(&t);
	ft_lstndump(&t);
	return (0);
}
