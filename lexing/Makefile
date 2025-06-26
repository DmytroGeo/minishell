# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 16:44:12 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/06/25 17:33:59 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = liblexing.a
AR = ar rcs
CC = cc
LIBFT = ../libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRC = ft_toknew \
		ft_tokadd_front \
		ft_toksize \
		ft_toklast \
		ft_tokadd_back \
		ft_tokdelone \
		ft_tokclear \
		ft_tokindex \
		ft_tokfind \
		ft_splitter \
		read_line \
		lexing

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I../libft -I../execution

# “Hey compiler, also search in ../libft and ft (your local headers folder) for any #include "..." directives.”
# Keeps path handling in the build system, not the code.

# Lets your code just say #include "libft.h".

# You can update the include path once in the Makefile if you restructure things.

# Scales better across large projects.

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ../libft

$(NAME): $(LIBFT) $(OBJS)
	@$(AR) $(NAME) $(OBJS)

# $(NAME): $(LIBFT) $(OBJS)
# 	@cp $(LIBFT) $(NAME)
# 	@$(AR) $(NAME) $(OBJS)

# The line @cp $(LIBFT) $(NAME) works as follows: 

# $(LIBFT) expands to libft/libft.a, which is the compiled static library of the libft project.

# $(NAME) expands to liblexing.a, which is the name of the static library being created by this Makefile.

# cp libft/libft.a liblexing.a copies the libft.a file from the libft directory and renames it as liblexing.a.

# This step ensures that liblexing.a starts as a copy of libft.a.

# Then, the command @$(AR) $(NAME) $(OBJS) adds the object files into liblexing.a,

# making it a combined static library that includes both libft and liblexing functionalities.

# EDIT: I abandoned this approach because I need to be able to change each library without affecting the other ones.

# otherwise there's a base thing everything else depends on and that's a recipe for disaster.


# Add test target for creating an executable from read_line.c
TEST = test_lexing

test: $(NAME)
	@$(CC) $(CFLAGS) read_line.c -L. -llexing -L../libft -lft -lreadline -I. -I../libft -o $(TEST)
	@./$(TEST)

clean: 
	@rm -f $(OBJS)
	@$(MAKE) -C ../libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ../libft fclean

re: fclean all

.PHONY: all fclean clean re
