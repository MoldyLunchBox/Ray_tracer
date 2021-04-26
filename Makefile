# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amya <amya@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 16:50:40 by amya              #+#    #+#              #
#    Updated: 2021/04/24 10:26:49 by amya             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= 	main.c \
			plane.c\
			ray.c\
			sphere.c\
			cone.c\
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
			li.c\
			val2.c\
			texture2.c\
			raytrace2.c\
			event.c\
			cone2.c\
			data_malloc2.c\
			pars_error_checker.c\
			data_limited_cylinder.c\
			box.c\
			data_box.c\
			extra_tools.c\
			data_limited_cone.c\
			box_slice.c\
			event_2.c\
			cylinder_limit.c\
			cylinder.c\
			direct_light.c\
			negative_obj.c\
			limited_cone.c\
			sorting.c\
			disruption.c\
			intersection.c\
			filters.c\
			

HEADER = 	header/data.h\
			header/ray.h\
			header/rt.h\
			header/vector.h\

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME 	= RT

CFLAGS = -Wall -Wextra -Werror 

INCLUDE	= -I /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/include \
	-I /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/include \

LIB = -L /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/lib \
	-L   /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/lib \

SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image

SRC_DIR = ./src

OBJ_DIR = ./obj

LIBFT_DIR = ./libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a


CC = @gcc  -g

all : $(NAME)

$(LIBFT_LIB): force
	@make  -C $(LIBFT_DIR)
force:

$(NAME) : $(LIBFT_LIB) $(OBJ)
	@gcc  $(CFLAGS) $(OBJ)  -o $(NAME) $(INCLUDE) $(LIB)  $(SDL) $(LIBFT_LIB)
	@echo "\033[92mDone for RTV1\033[0m"

$(OBJ_DIR):
	@-mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@gcc -c -g $(CFLAGS) $(INCLUDE) $< -o $@

clean :
	@make clean -C ./libft/
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make fclean -C ./libft/
	@rm -rf $(NAME)

re : fclean all
