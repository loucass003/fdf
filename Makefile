# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:49:27 by llelievr          #+#    #+#              #
#    Updated: 2019/01/29 22:20:50 by llelievr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include src.mk

NAME	=fdf
OBJ		=$(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		=gcc
CFLAGS	=-Wall -Werror -Wextra -flto -O3 -ffast-math

# mlx library
MLX_INC	=-I /usr/local/include
MLX_LNK	=-L /usr/local/lib -lmlx

# ft library
FT		=./libft
FT_LIB	=$(addprefix $(FT), libft.a)
FT_INC	=-I ./libft/includes
FT_LNK	=-L ./libft -lft
FT_TASK =

# directories
SRCDIR	=./srcs/
INCDIR	=./includes/
OBJDIR	=./objs/

# OS COMPATIBILITES
UNAME :=$(shell uname)
ifeq ($(UNAME), Linux)
	MLX_LNK += -lXext -lX11
else
	MLX_LNK += -framework OpenGL -framework AppKit
endif

all: $(FT_LIB) $(NAME)

dev: CFLAGS =-g
dev: FT_TASK = dev 
dev: re

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -j4 -C $(FT)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)



clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

get_files:
	$(shell find srcs -type f | sed 's/srcs\///g' | sed 's/^/SRC+=/' > src.mk)

re: fclean all
