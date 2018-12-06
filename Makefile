# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:49:27 by llelievr          #+#    #+#              #
#    Updated: 2018/12/03 16:57:51 by llelievr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
SRC		= $(shell find srcs -type f | sed 's\#^srcs/\#\#')
OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# mlx library
MLX_INC	= -I /usr/local/includes
MLX_LNK	= -L /usr/local/lib

# ft library
FT		= ./includes/libft/
FT_LIB	= $(addprefix $(FT), libft.a)
FT_INC	= -I ./includes/libft/includes
FT_LNK	= -L ./includes/libft -l ft
FT_TASK = all;

# directories
SRCDIR	= ./srcs/
INCDIR	= ./includes/
OBJDIR	= ./objs/

# OS COMPATIBILITES
UNAME :=$(shell uname)
ifeq ($(UNAME), Linux)
	MLX_LNK			+=	-lmlx -lft -lXext -lX11 -lm
else
	MLX_LMK			+=	-framework OpenGL -framework AppKit
endif

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT) $(FT_TASK)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

dev: CFLAGS+=-g
dev: FT_TASK = dev 
dev: re

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all
