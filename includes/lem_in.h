/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:05:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/01 00:26:45 by fbabin           ###   ########.fr       */
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

typedef struct		s_env
{
	int				**coords;
	t_list			*t;
	t_list			*room_state;
	int				step;
	int				screen_x;
	int				screen_y;
	int				b_x;
	int				b_y;
	int				s_x;
	int				s_y;
	int				x;
	int				y;
	int				scale;
	void			*mlx_ptr;
	void			*win_ptr;
}					t_env;

typedef struct		s_bres
{
	int				dx;
	int				dy;
	float			m;
	int				adjust;
	float			offset;
	float			threshold;
	float			delta;
	int				x;
	int				y;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
}					t_bres;

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

/*
** ------------------------------- PARSE FUNCTIONS ----------------------------
*/

int					somme_sizes(int *roads_size, int nb_roads, int i, int n);
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
void				ft_launch_dump(t_list *list);

int					new_bfs(t_list **ntv, t_list **visited, t_room *dest);
int					solver(t_list **t, int nb_ants, int option);
int					find_cycles(t_list **list, int nb_ants);
int					find_cycles2(t_list **paths, int n);
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
void				egalize_ants2(int *nb_ants, int nb_roads, int n);
void				egalize_ants(int *nb_ants, int nb_roads, int n);

/*
** ------------------------------- VISU FUNCTIONS -----------------------------
*/

t_list				*get_room_states(void);
void				ft_int2dumpx(int **array, int x);
t_env				*generate_map(t_list **t);
int					deal_key(int key, void *param);
void				bresenham(t_env *env, t_dot *d1, t_dot *d2);
t_room				*find_room_by_name(t_list **t, char *str);
void				convert_coords(t_env *env, t_list **t);
void				draw_square(t_env *env, int x, int y, int color);
void				draw_l(t_env *env, t_room *r);
void				display_dots(t_env *env, t_list **t);
void				disp_steps(t_env *env, t_list **rs, t_list **main,
						int step);
void				set_start_end(t_list **t);

/*
** ------------------------------- FREE FUNCTIONS -----------------------------
*/

void				ft_lstnfree(t_list **t);
void				ft_lstnfree2(t_list **t);
void				freechar2(char **tab);
void				freenames(char ***names, t_list **paths);
void				freetabs(int **tabs, t_list **paths);
void				freenode(t_room *t);
void				free_listss(t_list *paths);
void				freeit(t_list *path);

#endif
