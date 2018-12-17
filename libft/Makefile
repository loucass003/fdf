# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 14:49:27 by llelievr          #+#    #+#              #
#    Updated: 2018/12/17 13:21:06 by llelievr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME =libft.a
CFLAGS=-Wall -Werror -Wextra -I ./includes 
SRC=./ft_abs.c \
	./ft_absf.c \
	./ft_atoi.c \
	./ft_bzero.c \
	./ft_foreach.c \
	./ft_gnl.c \
	./ft_isalnum.c \
	./ft_isalpha.c \
	./ft_isascii.c \
	./ft_isdigit.c \
	./ft_isprint.c \
	./ft_isspace.c \
	./ft_itoa.c \
	./ft_lstadd.c \
	./ft_lstdel.c \
	./ft_lstdelone.c \
	./ft_lstiter.c \
	./ft_lstmap.c \
	./ft_lstnew.c \
	./ft_lstput.c \
	./ft_mat4_identity.c \
	./ft_mat4_mul.c \
	./ft_mat4_mulv.c \
	./ft_mat4_rotation.c \
	./ft_mat4_scale.c \
	./ft_mat4_translation.c \
	./ft_memalloc.c \
	./ft_memccpy.c \
	./ft_memchr.c \
	./ft_memcmp.c \
	./ft_memcpy.c \
	./ft_memdel.c \
	./ft_memmove.c \
	./ft_memset.c \
	./ft_realloc.c \
	./ft_pixel_add.c \
	./ft_pixel_div.c \
	./ft_pixel_mul.c \
	./ft_pixel_sub.c \
	./ft_pow.c \
	./ft_putchar.c \
	./ft_putchar_fd.c \
	./ft_putendl.c \
	./ft_putendl_fd.c \
	./ft_putnbr.c \
	./ft_putnbr_fd.c \
	./ft_putstr.c \
	./ft_putstr_fd.c \
	./ft_sqrt.c \
	./ft_strcat.c \
	./ft_strchr.c \
	./ft_strclr.c \
	./ft_strcmp.c \
	./ft_strcpy.c \
	./ft_strdel.c \
	./ft_strdup.c \
	./ft_strequ.c \
	./ft_striter.c \
	./ft_striteri.c \
	./ft_strjoin.c \
	./ft_strlcat.c \
	./ft_strlen.c \
	./ft_strmap.c \
	./ft_strmapi.c \
	./ft_strncat.c \
	./ft_strncmp.c \
	./ft_strncpy.c \
	./ft_strnequ.c \
	./ft_strnew.c \
	./ft_strnstr.c \
	./ft_strrchr.c \
	./ft_strsplit.c \
	./ft_strstr.c \
	./ft_strsub.c \
	./ft_strtrim.c \
	./ft_tolower.c \
	./ft_toupper.c \
	./ft_vec2_add.c \
	./ft_vec2_div.c \
	./ft_vec2_dot.c \
	./ft_vec2_inv.c \
	./ft_vec2_len.c \
	./ft_vec2_mul.c \
	./ft_vec2_norm.c \
	./ft_vec2_sub.c \
	./ft_vec3_add.c \
	./ft_vec3_cross.c \
	./ft_vec3_div.c \
	./ft_vec3_dot.c \
	./ft_vec3_inv.c \
	./ft_vec3_len.c \
	./ft_vec3_mul.c \
	./ft_vec3_norm.c \
	./ft_vec3_sub.c 
OBJ=$(SRC:.c=.o)

ERR="\e[1;31m"
SUCCESS="\e[1;32m"
WARN="\e[1;33m"
INFO="\e[1;36m"
RESET="\e[1;0m"

all: $(NAME)

$(NAME): $(OBJ)
	@printf $(INFO)"CREATING LIBRARY ($(NAME)) "$(RESET)"\n"
	@ar cr $(NAME) $(OBJ)

%.o: %.c
	@printf "%s" $<
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "%*s\e[1;36m%s\e[1;0m]\n" $$((80 - $(shell echo $< | awk '{print length}'))) "[" "DONE"

dev: CFLAGS += -g
dev: re

clean:
	@echo "Cleaning objs"
	@rm -f $(OBJ)

fclean: clean
	@echo "Cleaning library"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
