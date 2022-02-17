# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 08:20:09 by cberganz          #+#    #+#              #
#    Updated: 2022/02/17 11:09:07 by cberganz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo

NAME_BONUS	= philo_bonus

INCLUDE		= include/

HEADER		= $(INCLUDE)philo.h

HEADER_BONUS= $(INCLUDE)philo_bonus.h

CC			= clang

CFLAGS		= -Wall -Wextra -Werror#-fsanitize=thread -g3

SRC_FILES =	philo.c						\
			philo_alive.c				\
		  	philo_do.c					\
			utils_threads.c				\
			utils.c						\
			parse_arguments.c

SRC_BONUS_FILES =	main_bonus.c			\
					masters_bonus.c			\
		  			philo_do_bonus.c		\
					utils_forking_bonus.c	\
					utils_bonus.c			\
					exit_bonus.c			\
					parse_arguments_bonus.c

SRC_DIR		= src/
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

SRC_BONUS_DIR	= src_bonus/
SRC_BONUS		= $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS_FILES))

OBJ_DIR		= objs/
OBJ_FILES	= $(SRC_FILES:.c=.o)
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

OBJ_BONUS_DIR	= objs_bonus/
OBJ_BONUS_FILES	= $(SRC_BONUS_FILES:.c=.o)
OBJ_BONUS		= $(addprefix $(OBJ_BONUS_DIR), $(OBJ_BONUS_FILES))

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -pthread

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) -pthread

$(OBJ_DIR):
	mkdir -p $@
$(OBJ_BONUS_DIR):
	mkdir -p $@

$(OBJ): | $(OBJ_DIR)
$(OBJ_BONUS): | $(OBJ_BONUS_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.PHONY : all clean fclean re
