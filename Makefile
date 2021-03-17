# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amya <amya@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/12 12:17:42 by ramoukha          #+#    #+#              #
#    Updated: 2021/03/17 17:03:15 by amya             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMP = gcc -Werror -Wextra -Wall -g
SRC = srcs/main.c srcs/vec_calc.c  srcs/transforms.c srcs/ft_intersection.c srcs/tools.c srcs/checker.c srcs/init.c srcs/normal.c srcs/tools_2.c srcs/light.c
OB =  srcs/main.o srcs/vec_calc.o srcs/transforms.o  srcs/ft_intersection.o srcs/tools.o srcs/checker.o srcs/init.o srcs/normal.o srcs/tools_2.o srcs/light.o
INC_DIR = ./includes/
INC = ./includes/rtv1.h
OB = $(SRC:.c=.o)
NAME =  a.out
LIBFLAGS =  -g -L ./libft -lft -lpthread -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(OB)
	@make -C libft/
	$(COMP) -g -o $(NAME) $(OB) $(LIBFLAGS)
	@printf "\033[00;32m"
	@printf "BINARY CREATED\n"
	@printf "\033[00;0m"

%.o : %.c $(INC)
	$(COMP) -c -o $@ $< -I $(INC_DIR)

clean:
	@make -C libft/ clean
	# @make -C miniLibX clean
	@rm -f $(OB)
	@printf "\033[00;32m"
	@printf "OBJECTS REMOVED\n"
	@printf "\033[00;0m"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@printf "\033[00;32m"
	@printf "BINARY REMOVED\n"
	@printf "\033[00;0m"
re: fclean all
