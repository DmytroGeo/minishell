# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 17:20:58 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/07/15 17:00:15 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libparsing.a
AR = ar rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRC = del_tok_content \
		ft_init_envp_and_prompt \
		export_and_unset_variables \
		find_commands_and_arguments \
		find_infiles \
		find_outfiles \
		free_main \
		free_token_chain \
		ft_infile_error \
		ft_outfile_error \
		heredoc \
		is_some_token \
		is_some_token2 \
		parsing \
		syntax_conditions

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