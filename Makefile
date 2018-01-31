# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 21:15:36 by fbabin            #+#    #+#              #
#    Updated: 2018/01/31 16:17:00 by arobion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN			= lem-in

CC				= gcc -g3
CFLAGS			= -Wall -Werror -Wextra

_SRCS			=	lem_in.c get_rooms.c get_rooms2.c get_rooms3.c \
					get_pipes.c get_pipes2.c get_pipes3.c \
					launchers.c freeer.c \
					ft_displays.c atoi_check.c solver.c roads.c \
					affichage.c affichage_cycle.c affichage_move.c \
					affichage_first_ants.c affichage2.c lem_in2.c \
					solver2.c solver3.c freeer2.c

_LIBFT			=	libft.a
HEADER_DIR		=	includes
HEADER			=	$(HEADER_DIR)/lem_in.h

SRCS_DIR		= srcs
LIB_DIR			= libft
SRCS			= $(addprefix $(SRCS_DIR)/, $(_SRCS))
LIBFT			= $(addprefix $(LIB_DIR)/, $(_LIBFT))
OBJS			= $(_SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: $(LEM_IN)

$(LEM_IN): $(HEADER) $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) -o $(LEM_IN) $(OBJS) -L$(LIB_DIR) -lft -I $(HEADER_DIR)
		@echo "$(LEM_IN) : $(_GREEN)Done$(_END)"

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(OBJS)
		@echo "$(LEM_IN) clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(LEM_IN)
		@echo "$(LEM_IN) fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
