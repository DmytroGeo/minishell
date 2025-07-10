# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 11:38:45 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/07/08 10:27:08 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libexecution.a
CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRCS = $(shell find . -name '*.c') # remove this before eval

# src/close_pipes.c \
# 			src/flags_and_paths.c \
# 			src/dup_read_and_write.c \
# 			src/execute.c \
# 			src/initialise.c \
# 			src/free_and_exit.c \
# 			src/proc_call.c \
# 			src/process_loop.c \
# 			src/wait_for_processes.c \
# 			execution.c \
# 			lists/ft_find_node.c \
# 			lists/ft_intarr_free.c \
# 			lists/ft_exec_lstadd_front.c \
# 			lists/ft_perror.c \
# 			lists/ft_exec_lstclear.c \
# 			lists/ft_exec_lstnew.c
			
OBJS = $(SRCS:.c=.o)

# OBJS = $(patsubst .c, .o, $(SRCS))

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I../libft -I../parsing -I../lexing 

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re