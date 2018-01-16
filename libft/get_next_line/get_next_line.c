/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:04:29 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/16 23:08:45 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				get_next_line(const int fd, char **line)
{
	static char		buff[BUFF_SIZE + 1];
	int				ret;
	int				endl;
	int				idx;

	if (!line || !(*line = ft_strnew(BUFF_SIZE)) || BUFF_SIZE < 1)
		return (-1);
	while (1)
	{
		if (!*buff)
			ft_bzero(buff, BUFF_SIZE + 1);
		if (!*buff && (ret = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		if (!ret && **line)
			return (1);
		if (!ret && !*buff)
			return (0);
		idx = ft_strchrindex(buff, '\n');
		if ((endl = ft_charinset('\n', buff)) < 0 ||
				!(*line = ft_strnjoinclr(*line, buff, idx, 1)))
			return (-1);
		ft_strcpy((char*)buff, &(buff[(buff[idx] == '\n') ? (idx + 1) : idx]));
		if (endl)
			return (1);
	}
}
