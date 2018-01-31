/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:05:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/01/31 11:54:31 by arobion          ###   ########.fr       */
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
int					ft_verif_pipe_format(char *line);
char				*get_ants(int *nb_ants);

int					ft_verif_line_is_comm(char *line);
long long			ft_atoi_check(const char *str);
int					ft_launch_cmp(t_room *crawler, const char *name);
void				ft_launch_pushback(t_room *crawler, t_room *room);
t_room				*init_room(const char *str, int x, int y);

void				ft_lstndump(t_list **list);

int					new_bfs(t_list **ntv, t_list **visited, t_room *dest);
int					solver(t_list **t, int nb_ants, int option);
int					find_cycles(t_list **list, int nb_ants);
int					get_start_end(t_list **list, t_list **start, t_list **end);
int					ft_lstin(t_list **begin_list, void *data_ref,\
		int (*cmp)(), size_t size);
void				ft_lstremovefirst(t_list **begin_list, void *content_ref,\
		int (*cmp)(), size_t size);
void				ft_lstpushlist(t_list **begin_list, t_list **add,\
		int (*cmp)(), size_t size);

void				affichage(t_list **paths, int *nb_ants, int nb_cycles);
void				print_at_this_cycle(int **tabs, char ***names,\
		t_list **paths);
void				move_all_ants(int **tabs, t_list **paths);
void				place_each_new_ants(int **tab, t_list **paths,\
		int *nb_ants, int n_c);
char				***mall_names(t_list **paths);
void				print_and_norme(char *line, int *b);
/*
** ------------------------------- FREE FUNCTIONS -----------------------------
*/

void				ft_lstnfree(t_list **t);
void				ft_lstnfree2(t_list **t);
void				freechar2(char **tab);
void				freenames(char ***names, t_list **paths);
void				freetabs(int **tabs, t_list **paths);
void				freenode(t_room *t);

#endif
