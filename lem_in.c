/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:21:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/30 15:31:29 by arobion          ###   ########.fr       */
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

int			main3(int nb_ants, t_list *t, int option)
{
	if (!solver(&t, nb_ants, option))
	{
		ft_lstnfree(&t);
		return (write(1, "ERROR\n", 6));
	}
	ft_lstnfree(&t);
	return (1);
}

int			main2(char *line, int nb_ants, t_list *t, int option)
{
	if (line == NULL)
	{
		if (!solver(&t, nb_ants, option))
		{
			ft_lstnfree(&t);
			return (write(1, "ERROR\n", 6));
		}
		ft_lstnfree(&t);
		return (0);
	}
	if (!(get_pipes(line, &t)))
	{
		if (!solver(&t, nb_ants, option))
		{
			ft_lstnfree(&t);
			return (write(1, "ERROR\n", 6));
		}
		ft_lstnfree(&t);
		return (0);
	}
	return (main3(nb_ants, t, option));
}

void		earn_opt(int argc, char **argv, int *option)
{
	*option = 0;
	if (argc == 2)
	{
		if (strcmp(argv[1], "-p") == 0)
			*option = 1;
	}
}

int			main(int argc, char **argv)
{
	t_list	*t;
	char	*line;
	int		nb_ants;
	int		option;

	t = NULL;
	nb_ants = 0;
	earn_opt(argc, argv, &option);
	if (!(line = get_ants(&nb_ants)))
		return (ft_printf("ERROR\n"));
	if (nb_ants == 0)
	{
		free(line);
		return (ft_printf("ERROR\n"));
	}
	line = get_rooms(line, &t);
	return (main2(line, nb_ants, t, option));
}
