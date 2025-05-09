# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 17:18:32 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/05/09 17:28:33 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

# helper libraries:

LIBFT = ./libft/libft.a
LEXING = ./lexing/liblexing.a
PARSING = ./parsing/libparsing.a

SRC = pwd \
		main

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I./libft -I./lexing -I./parsing

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(LEXING):
	@$(MAKE) -C ./lexing

$(PARSING):
	@$(MAKE) -C ./parsing

$(NAME): $(OBJS) $(LIBFT) $(LEXING) $(PARSING)
	$(CC) $(CFLAGS) $(OBJS) -L./lexing -llexing -L./libft -lft -L./parsing -lparsing -lreadline -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C ./parsing clean
	@$(MAKE) -C ./lexing clean
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./parsing fclean
	@$(MAKE) -C ./lexing fclean
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re