# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 11:20:28 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/07/25 17:22:45 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = ./libft/libft.a
OBJ_FOLDER = ./obj
SRC_FOLDER = ./src
INC_FOLDER = ./inc

INCLUDES = -I./libft -I$(INC_FOLDER)

SRCS = $(SRC_FOLDER)/main.c \
		$(SRC_FOLDER)/lexing/ft_dlstadd_back.c \
		$(SRC_FOLDER)/lexing/del_tok_content.c \
		$(SRC_FOLDER)/lexing/free_token_chain.c \
		$(SRC_FOLDER)/lexing/ft_dlstadd_front.c \
		$(SRC_FOLDER)/lexing/ft_dlstnew.c \
		$(SRC_FOLDER)/lexing/free_cshell.c \
		$(SRC_FOLDER)/lexing/ft_dlstsize.c \
		$(SRC_FOLDER)/lexing/ft_perror.c \
		$(SRC_FOLDER)/lexing/find_next_tok.c \
		$(SRC_FOLDER)/lexing/init_tok_cont.c \
		$(SRC_FOLDER)/lexing/lexing_utils.c \
		$(SRC_FOLDER)/lexing/lexing.c \
		$(SRC_FOLDER)/lexing/quote_utils.c \
		$(SRC_FOLDER)/parsing/ft_init_main.c \
		$(SRC_FOLDER)/parsing/find_commands_and_arguments.c \
		$(SRC_FOLDER)/parsing/find_infiles.c \
		$(SRC_FOLDER)/parsing/find_outfiles.c \
		$(SRC_FOLDER)/parsing/ft_infile_error.c \
		$(SRC_FOLDER)/parsing/ft_outfile_error.c \
		$(SRC_FOLDER)/parsing/heredoc.c \
		$(SRC_FOLDER)/parsing/is_some_token.c \
		$(SRC_FOLDER)/parsing/is_some_token2.c \
		$(SRC_FOLDER)/parsing/parsing.c \
		$(SRC_FOLDER)/parsing/syntax_conditions.c \
		$(SRC_FOLDER)/built-ins/change_directory.c \
		$(SRC_FOLDER)/built-ins/execute_built_ins.c \
		$(SRC_FOLDER)/built-ins/export_all_variables.c \
		$(SRC_FOLDER)/built-ins/ft_echo.c \
		$(SRC_FOLDER)/built-ins/ft_exit.c \
		$(SRC_FOLDER)/built-ins/ft_pwd.c \
		$(SRC_FOLDER)/built-ins/is_valid_variable.c \
		$(SRC_FOLDER)/built-ins/print_envp.c \
		$(SRC_FOLDER)/built-ins/unset_all_variables.c \
		$(SRC_FOLDER)/execution/close_pipes.c \
		$(SRC_FOLDER)/execution/proc_call.c \
		$(SRC_FOLDER)/execution/dup_infiles_and_outfiles.c \
		$(SRC_FOLDER)/execution/execute_in_main.c \
		$(SRC_FOLDER)/execution/execute_in_child.c \
		$(SRC_FOLDER)/execution/initialise_pipes.c \
		$(SRC_FOLDER)/execution/process_loop.c \
		$(SRC_FOLDER)/execution/wait_for_processes.c \
		$(SRC_FOLDER)/execution/execution.c

OBJS = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))

all: $(OBJ_FOLDER) $(NAME)

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lreadline -o $(NAME)

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJ_FOLDER)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
