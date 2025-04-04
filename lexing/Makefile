# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 16:44:12 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/04/04 20:18:35 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexing.a
AR = ar rcs
CC = cc
LIBFT = ../libft/libft.a
CFLAGS = -Wall -Wextra -Werror
SRC = ft_toknew \
		ft_tokadd_front \
		ft_toksize \
		ft_toklast \
		ft_tokadd_back \
		ft_tokdelone \
		ft_tokclear \
		ft_tokindex \
		ft_tokfind \
		lexing

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ../libft

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS)

# The line @cp $(LIBFT) $(NAME) works as follows: 

# $(LIBFT) expands to libft/libft.a, which is the compiled static library of the libft project.

# $(NAME) expands to libftprintf.a, which is the name of the static library being created by this Makefile.

# cp libft/libft.a libftprintf.a copies the libft.a file from the libft directory and renames it as libftprintf.a.

# This step ensures that libftprintf.a starts as a copy of libft.a.

# Then, the command @$(AR) $(NAME) $(OBJS) adds the object files from ft_printf and utils ($(OBJS)) into libftprintf.a,

# making it a combined static library that includes both libft and ft_printf functionalities.

clean: 
	@rm -f $(OBJS)
	@$(MAKE) -C ../libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ../libft fclean

re: fclean all

.PHONY: all fclean clean re
