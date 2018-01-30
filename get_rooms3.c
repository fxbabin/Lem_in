/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:37:18 by arobion           #+#    #+#             */
/*   Updated: 2018/01/30 15:31:11 by arobion          ###   ########.fr       */
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
