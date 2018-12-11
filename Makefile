# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:49:27 by llelievr          #+#    #+#              #
#    Updated: 2018/12/10 17:42:12 by llelievr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
SRC		= $(shell find srcs -type f | sed 's\#^srcs/\#\#')
OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra 

# mlx library
MLX_INC	= -I /usr/local/include
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
	MLX_LNK += -lmlx -lXext -lX11
else
	MLX_LNK += -lmlx -framework OpenGL -framework AppKit
endif

all: obj $(FT_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -j4 -C $(FT) $(FT_TASK)

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
