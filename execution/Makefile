# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 11:38:45 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/07/18 13:40:35 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libexecution.a
CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRCS = execution_utils/change_directory.c \
		execution_utils/execute_built_ins.c \
		execution_utils/export_all_variables.c \
		execution_utils/ft_echo.c \
		execution_utils/ft_exit.c \
		execution_utils/print_env.c \
		execution_utils/proc_call.c \
		execution_utils/unset_all_variables.c \
		src/close_pipes.c \
		src/dup_infiles_and_outfiles.c \
		src/execute_in_main.c \
		src/execute.c \
		src/initialise.c \
		src/process_loop.c \
		src/wait_for_processes.c \
		execution.c
			
OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I../libft -I../lexing -I../parsing

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re