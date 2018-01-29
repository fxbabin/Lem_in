/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:05:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/29 15:33:55 by arobion          ###   ########.fr       */
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
	int				boo;
	t_list			*pipes;
}					t_room;

/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

/*
** ------------------------------- PARSE FUNCTIONS ----------------------------
*/

char				*get_rooms(char *line, t_list **t);
char				**ft_verif_room_format(char *line);
int					ft_verif_room_validity(char **room);
int					ft_verif_room_is_uniq(char **room, t_list **t);

int					get_pipes(char *line, t_list **t);
int					ft_add_pipes_to_room(t_list **t, char *name1, char *name2);
int					ft_are_rooms_exists(char *line, int i, t_list **t);
int					ft_verif_unicity_of_pipe(t_room *room, char *name);

int					ft_verif_line_is_comm(char *line);
long long			ft_atoi_check(const char *str);
int					ft_launch_cmp(t_room *crawler, const char *name);
void				ft_launch_pushback(t_room *crawler, t_room *room);
t_room				*init_room(const char *str, int x, int y);

void				ft_lstndump(t_list **list);

int					solver(t_list **t, int nb_ants);
int					find_cycles(t_list **list, int nb_ants);

void				affichage(t_list **paths, int *nb_ants, int n, int _nb_cycles);
/*
** ------------------------------- FREE FUNCTIONS -----------------------------
*/

void				ft_lstnfree(t_list **t);
void				freechar2(char **tab);

#endif
