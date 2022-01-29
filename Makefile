# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 08:20:09 by cberganz          #+#    #+#              #
#    Updated: 2022/01/29 09:08:33 by cberganz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo

INCLUDE		= include/

HEADER		= $(INCLUDE)philo.h

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -O3

SRC_FILES=	philo.c						\
		  	philo_do.c					\
			utils_threads.c				\
			utils.c						\
			parse_arguments.c

SRC_DIR		= src/
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		= objs/
OBJ_FILES	= $(SRC_FILES:.c=.o)
OBJ			= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -pthread -g3

$(OBJ_DIR):
	mkdir -p $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@ -g3

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
