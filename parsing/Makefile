# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 17:20:58 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/06/25 17:33:48 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libparsing.a
AR = ar rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRC = parsing

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I../libft -I../lexing

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re