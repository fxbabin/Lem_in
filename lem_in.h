/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:05:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/22 19:18:03 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** --------------------------------- INCLUDES -------------------------------
*/

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

/*
** -------------------------------- STRUCTURES -------------------------------
*/

typedef struct		s_room
{
	const char		*name;
	int				x;
	int				y;
	int				b;
	t_list			*sup;
	t_list			*pipes;
}					t_room;

void				ft_lstndump(t_list **t);
void				freechar2(char **tab);
int					get_pipes(char *line, t_list **t);
int					ft_verif_line_is_comm(char *line);
int					ft_launch_cmp(t_room *crawler, const char *name);
long long			ft_atoi_check(const char *str);
char				*get_rooms(char *line, t_list **t);
t_room				*init_room(const char *str, int x, int y);
/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

/*
** ------------------------------- SORT FUNCTIONS -----------------------------
*/

#endif
