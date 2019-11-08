# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/02 17:24:08 by nlavrine          #+#    #+#              #
#    Updated: 2019/11/08 18:11:51 by nlavrine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = wolf3d

SRC =	main.c	\
		error.c	\
		parse.c	\
		split.c	\
		sys_out.c	\
		wolf3d.c	\
		loop.c		\
		draw.c		\
		ray_casting.c	\
		control.c		\
		textures.c

CC = gcc
FLAGS = -Wall -Wextra -Werror 
SRC_DIR = srcs
H_DIR = includes
OBJ_DIR = obj
OBJ_DIR2 = obj/fractals
LIB = libft/libft.a
PRINTF = libft/ft_printf/libftprintf.a
GREEN = \033[0;32m
IMG_FRAME = -framework SDL2 -F . -framework SDL2_image -framework SDL2_ttf -rpath .

INCLUDES = 	-I./frameworks/SDL2.framework/Headers/ \
			-I./frameworks/SDL2_image.framework/Headers/ \
			-I./frameworks/SDL2_ttf.framework/Headers/ \
			-I./frameworks/SDL2_mixer.framework/Headers/ \


FRAMEWORKS =  	-F./frameworks \
    			-rpath ./frameworks \
    			-framework AppKit -framework OpenGL \
    			-framework SDL2 -framework SDL2_image \
    			-framework SDL2_ttf \


SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME) 

$(NAME): $(LIB) $(PRINTF) $(OBJS)
		@echo "$(GREEN)Compile $(NAME)"
		@$(CC) $(FLAGS)  -lpthread  -lm $(FRAMEWORKS) $(OBJS) $(PRINTF) $(LIB) $(PRINTF) -o $(NAME) $(INCLUDES)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR2)
		@$(CC) $(FLAGS) -o $@ -c $< -I $(H_DIR) $(INCLUDES)

$(LIB):
	@echo "$(GREEN)Compile libft"
	@make -C ./libft/

$(PRINTF):
	@echo "$(GREEN)Compile ft_printf"
	@make -C ./libft/ft_printf/

clean:
	@echo "$(GREEN)Clear objs"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR2)
	@make -C ./libft/ clean
	@make -C ./libft/ft_printf/ clean

fclean: clean
	@echo "$(GREEN)Clear $(NAME)"
	@rm -f $(NAME)
	@make -C ./libft/ fclean
	@make -C ./libft/ft_printf/ fclean

re: fclean all