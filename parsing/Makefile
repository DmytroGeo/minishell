# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 17:20:58 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/07/05 15:40:18 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libparsing.a
AR = ar rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRC = environment_functs \
		parsing \
		expand_variables \
		find_commands_and_arguments \
		find_infiles \
		find_number_of_files \
		find_outfiles \
		proc_call \
		init_simple_command \
		is_some_token

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