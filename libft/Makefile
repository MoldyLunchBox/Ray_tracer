# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 23:14:13 by yoelguer          #+#    #+#              #
#    Updated: 2020/01/31 00:07:51 by yoelguer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OC 		= ft_isalpha.c  ft_memccpy.c ft_memset.c ft_putnbr.c ft_strcat.c ft_strdup.c ft_strlen.c ft_strnequ.c ft_strstr.c\
ft_isascii.c ft_memchr.c ft_putnbr_fd.c ft_strchr.c ft_strequ.c ft_strmap.c ft_strnew.c ft_strsub.c\
ft_atoi.c ft_isdigit.c ft_memcmp.c ft_putchar.c ft_putstr.c ft_strclr.c ft_strmapi.c ft_strnstr.c ft_strtrim.c\
ft_bzero.c ft_isprint.c  ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strcmp.c ft_striteri.c ft_strncat.c ft_strrchr.c ft_tolower.c\
ft_itoa.c ft_memdel.c ft_putendl.c ft_strcpy.c ft_strjoin.c ft_strncmp.c ft_toupper.c\
ft_isalnum.c ft_memalloc.c ft_memmove.c ft_putendl_fd.c ft_strdel.c ft_strlcat.c ft_strncpy.c ft_strsplit.c\
get_next_line.c ft_count_words_sep.c ft_max.c ft_tabnew_two.c\

HEADER = libft.h\

OB = $(addprefix $(OBJ_DIR)/,$(OC:.c=.o))

OBJ_DIR = ./obj

NAME 	= libft.a

CC		= @gcc

all : $(NAME)

$(NAME) : $(OB)
	@ar rc libft.a $(OB)
	@echo "\033[92mDone for libft\033[0m"

$(OBJ_DIR):
	@-mkdir $(OBJ_DIR)

$(OB): $(OBJ_DIR)/%.o : ./%.c $(HEADER) | $(OBJ_DIR)
	@gcc -c  $(INCLUDE) $< -o $@ 

clean :
	@rm -rf $(OBJ_DIR)
fclean : clean
	@rm -f $(NAME)

norme:
	@norminette $(OC) libft.h

re : fclean all
