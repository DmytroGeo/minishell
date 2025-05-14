# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 11:38:45 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/05/13 18:36:50 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libexecution.a
LL = liblists.a
CC = cc
AR = ar rcs
FLAGS = -Wall -Wextra -Werror -g3
SRCS = src/close_pipes.c \
			src/flags_and_paths.c \
			src/dup_read_and_write.c \
			src/execute.c \
			src/initialise.c \
			src/free_and_exit.c \
			src/proc_call.c \
			src/process_loop.c \
			src/wait_for_processes.c \
			execution.c
			
OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I../libft -I../lexing -I../parsing -I./lists

all: $(NAME)

$(LL):
	$(MAKE) -C lists

$(NAME): $(OBJS) $(LL)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re