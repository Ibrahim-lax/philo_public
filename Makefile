# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: librahim <librahim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/17 19:43:32 by librahim          #+#    #+#              #
#    Updated: 2024/12/12 00:29:57 by librahim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc

FLAGS = -Wall -Werror -Wextra  -g # -fsanitize=thread

SRC = data_init.c main.c p_exit.c the_dinner.c gettimeofday.c ftatoi.c launching_the_dinner.c the_dinner_ii.c

OBJ = data_init.o main.o p_exit.o the_dinner.o gettimeofday.o ftatol.o launching_the_dinner.o the_dinner_ii.o

HEADER = philo.h

all : $(NAME) clean

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
