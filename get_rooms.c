/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:42:56 by arobion           #+#    #+#             */
/*   Updated: 2018/01/22 17:44:26 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**ft_verif_room_format(char *line)
{
	char	**room;
	int		i;

	i = 0;
	if (line[0] == ' ')
		return (NULL);
	if (!(room = ft_strsplit(line, ' ')))
		return (NULL);
	while (room[i] != NULL)
		i++;
	if (i == 3)
		return (room);
	freechar2(room);
	return (NULL);
}

int		ft_verif_line_is_comm(char *line)
{
	if (line[0] == '#')
	{
		free(line);
		return (1);
	}
	return (0);
}

int		ft_verif_room_validity(char **room)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (room[0][0] == 'L')
		return (0);
	while (room[i][j] != '\0')
	{
		if (!(ft_isprint(room[i][j])) || room[i][j] == '-')
			return (0);
		j++;
	}
	j = 0;
	i++;
	if (room[i][0] == '-' || room[i][0] == '+')
		j = 1;
	while (room[i][j] != '\0')
	{
		if (!(ft_isdigit(room[i][j])))
			return (0);
		j++;
	}
	j = 0;
	i++;
	if (room[i][0] == '-' || room[i][0] == '+')
		j = 1;
	while (room[i][j] != '\0')
	{
		if (!(ft_isdigit(room[i][j])))
			return (0);
		j++;
	}
	return (1);
}

int		ft_launch_cmp(t_room *crawler, const char *current_room)
{
	return (ft_strcmp(crawler->name, current_room));
}

int		ft_are_int(long long x, long long y)
{
	if (x > 2147483647 || x < -2147483648)
		return (0);
	if (y > 2147483647 || y < -2147483648)
		return (0);
	return (1);
}

int		ft_pos_cmp(t_room *crawler, long long x, long long y)
{
	if (crawler->x == x && crawler->y == y)
		return (0);
	return (1);
}


int		ft_verif_room_is_uniq(char **room, t_list **t)
{
	t_list		*crawler;
	long long	x;
	long long	y;

	x = ft_atoi_check(room[1]);
	y = ft_atoi_check(room[2]);
	if (ft_are_int(x, y) == 0)
		return (0);
	crawler = *t;
	while (crawler)
	{
		if (!(ft_launch_cmp(crawler->content, room[0])))
			return (0);
		if (!(ft_pos_cmp(crawler->content, x, y)))
			return (0);
		crawler = crawler->next;
	}
	return (1);
}


char	*get_rooms(char *line, t_list **t)
{
	char	**room;
	int		b;

	(void)t;
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
	}
	if (ft_verif_line_is_comm(line) == 0)
	{
		if (!(room = ft_verif_room_format(line)))
		{
			ft_printf("%s\n", line);
			ft_printf("format invalide\n\n");
			return (line);
		}
		if (!(ft_verif_room_validity(room)))
		{
			ft_printf("%s\n", line);
			ft_printf("validite invalide\n\n");
			freechar2(room);
			return (line);
		}
		if (!(ft_verif_room_is_uniq(room, t)))
		{
			ft_printf("doublon\n\n");
			freechar2(room);
			free(line);
			return NULL;
		}
		ft_lstpushback(t, init_room(room[0], ft_atoi(room[1]), ft_atoi(room[2])), b);
		freechar2(room);
		free(line);
	}
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
		}
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if (!(room = ft_verif_room_format(line)))
		{
			ft_printf("%s\n", line);
			ft_printf("format invalide\n\n");
			return (line);
		}
		if (!(ft_verif_room_validity(room)))
		{
			ft_printf("%s\n", line);
			ft_printf("validite invalide\n\n");
			freechar2(room);
			return (line);
		}
		if (!(ft_verif_room_is_uniq(room, t)))
		{
			ft_printf("doublon\n\n");
			freechar2(room);
			free(line);
			return NULL;
		}
		ft_lstpushback(t, init_room(room[0], ft_atoi(room[1]), ft_atoi(room[2])), b);
		ft_printf("%s\n", line);
		ft_printf("c'est valide\n\n");
		freechar2(room);
		free(line);
	}
	return (line);
}

/*
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
		   }
		   if (n == 2)
		   {
		   if (!ft_checkpath(tab))
		   break ;

		   }
		   */	/*else
				  error*/
		//ft_lstpushback(t, init_room(tab[0],), 0);

		//if (!ft_strcmp(line, "##start"))
		//	break ;

		//ft_lstdump(t);
		//ft_char2dump(tab);
		//freechar2(tab);
		//	ft_printf("%s\n", line);

