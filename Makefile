#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/02 15:43:48 by apavlov           #+#    #+#              #
#    Updated: 2019/08/02 15:43:53 by apavlov          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

FLAGS =  -Wall -O3 -Wextra #-g -fsanitize=address #-Werror

NAME = RTv1

SRC =	main.c init.c math.c output.c parser.c\
		plane.c sphere.c render.c function.c check_line.c\
		pov.c user_events.c lights.c cylin.c cone.c\
		parser_routine.c changes.c editor.c

INC = includes/rt.h

SRC_DIR = ./src/

OBJ_DIR = ./obj/

INC_DIR = ./includes/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FT = ./libft/

FT_LIB	= $(addprefix $(FT),libft.a)

LINKS = -L$(FT) -l ft -lm

SDL_PATH = ./framework

INCLUDES = 		-I$(FT) -I$(INC_DIR) \
				-I./frameworks/SDL2.framework/Headers \
				-I./frameworks/SDL2_image.framework/Headers \
				-F./frameworks

FRAMEWORKS = 	-F./frameworks \
				-rpath ./frameworks \
				-framework AppKit -framework OpenGL \
				-framework SDL2 -framework SDL2_image \

all: obj_dir $(FT_LIB) $(NAME)
	echo 'Compilated!'

obj_dir:
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FRAMEWORKS) $(OBJ) $(LINKS) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean

re: fclean all
