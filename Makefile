# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amya <amya@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/22 16:14:13 by yoelguer          #+#    #+#              #
#    Updated: 2021/04/11 11:54:09 by amya             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= 	main.c \
			plane.c\
			ray.c\
			sphere.c\
			cylindre.c\
			cone.c\
			ring.c\
			vector.c\
			vector2.c\
			vector3.c\
			file.c\
			data_camera.c\
			data_sphere.c\
			data_malloc.c\
			data_plane.c\
			data_light.c\
			data_cone.c\
			data_ring.c\
			data_cylinder.c\
			ft_atof.c\
			raytrace.c\
			val.c\
			light.c\
			sdl.c\
			paraploid.c\
			data_paraploid.c\
			data_ellipsoid.c\
			texture.c\
			filtres.c\
			mb_filter.c\
			sepia_filtre.c\
			li.c\
			cube.c\
			data_cube.c\
			val2.c\
			texture2.c\
			raytrace2.c\
			event.c\
			cone2.c\
			data_malloc2.c\
			pars_error_checker.c\
			data_limited_cylinder.c\

HEADER = 	header/data.h\
			header/ray.h\
			header/rt.h\
			header/vector.h\

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME 	= RT

CFLAGS = -Wall -Wextra -Werror -g

INCLUDE	= -I /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/include \
	-I /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/include \

LIB = -L /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/lib \
	-L   /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/lib \

SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image

SRC_DIR = ./src

OBJ_DIR = ./obj

LIBFT_DIR = ./libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a


CC = @gcc

all : $(NAME)

$(LIBFT_LIB): force
	@make -C $(LIBFT_DIR)

force:


$(NAME) : $(LIBFT_LIB) $(OBJ)
	@gcc -g $(OBJ) $(CFLAGS) -o $(NAME) $(INCLUDE) $(LIB)  $(SDL) $(LIBFT_LIB)
	@echo "\033[92mDone for RTV1\033[0m"

$(OBJ_DIR):
	@-mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@gcc -c -g $(INCLUDE) $< -o $@

clean :
	@make clean -C ./libft/
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make fclean -C ./libft/
	@rm -rf $(NAME)

norme:
	@norminette $(SRC_DIR)

re : fclean all
