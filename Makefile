# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 17:18:32 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/06/25 17:31:16 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# helper libraries:

LIBFT = ./libft/libft.a
LEXING = ./lexing/liblexing.a
PARSING = ./parsing/libparsing.a
EXECUTION = ./execution/libexecution.a

SRC = main

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I./libft -I./lexing -I./parsing -I./execution 

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(LEXING):
	@$(MAKE) -C ./lexing

$(PARSING):
	@$(MAKE) -C ./parsing

$(EXECUTION): 
	@$(MAKE) -C ./execution

$(NAME): $(OBJS) $(LIBFT) $(LEXING) $(PARSING) $(EXECUTION)
	$(CC) $(CFLAGS) $(OBJS) -L./lexing -llexing -L./parsing -lparsing -L./execution -lexecution -L./libft -lft -lreadline -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C ./execution clean
	@$(MAKE) -C ./parsing clean
	@$(MAKE) -C ./lexing clean
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./execution fclean
	@$(MAKE) -C ./parsing fclean
	@$(MAKE) -C ./lexing fclean
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re