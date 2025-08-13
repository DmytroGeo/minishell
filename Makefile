# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 11:20:28 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/08/12 21:20:33 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = ./libft/libft.a
OBJ_FOLDER = ./obj
SRC_FOLDER = ./src

INCLUDES = -I./libft -I./inc

SRCS = $(SRC_FOLDER)/main.c \
		$(SRC_FOLDER)/signals/main_signal_handlers.c \
		$(SRC_FOLDER)/lexing/ft_dlstadd_back.c \
		$(SRC_FOLDER)/lexing/del_tok_content.c \
		$(SRC_FOLDER)/lexing/free_token_chain.c \
		$(SRC_FOLDER)/lexing/ft_dlstnew.c \
		$(SRC_FOLDER)/lexing/free_cshell.c \
		$(SRC_FOLDER)/lexing/ft_dlstsize.c \
		$(SRC_FOLDER)/lexing/find_next_tok.c \
		$(SRC_FOLDER)/lexing/find_next_tok_utils.c \
		$(SRC_FOLDER)/lexing/init_tok_cont.c \
		$(SRC_FOLDER)/lexing/lexing_utils.c \
		$(SRC_FOLDER)/lexing/lexing.c \
		$(SRC_FOLDER)/lexing/quotes_error.c \
		$(SRC_FOLDER)/expansions/do_all_expansions.c \
		$(SRC_FOLDER)/expansions/double_quote_expansion_utils.c \
		$(SRC_FOLDER)/expansions/double_quote_expansions.c \
		$(SRC_FOLDER)/expansions/expansion_utils.c \
		$(SRC_FOLDER)/expansions/single_quotes_expansion.c \
		$(SRC_FOLDER)/expansions/split_word.c \
		$(SRC_FOLDER)/expansions/split_word_utils.c \
		$(SRC_FOLDER)/expansions/var_expansion_utils.c \
		$(SRC_FOLDER)/expansions/var_expansion.c \
		$(SRC_FOLDER)/parsing/ft_init_main.c \
		$(SRC_FOLDER)/parsing/find_commands_and_arguments.c \
		$(SRC_FOLDER)/parsing/find_infiles_and_outfiles.c \
		$(SRC_FOLDER)/parsing/find_infiles_and_outfiles_utils.c \
		$(SRC_FOLDER)/parsing/file_errors.c \
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
		$(SRC_FOLDER)/execution/do_redirections.c \
		$(SRC_FOLDER)/execution/execute_in_main.c \
		$(SRC_FOLDER)/execution/execute_in_child.c \
		$(SRC_FOLDER)/execution/execute_in_child_utils.c \
		$(SRC_FOLDER)/execution/initialise_pipes.c \
		$(SRC_FOLDER)/execution/process_loop.c \
		$(SRC_FOLDER)/execution/wait_for_processes.c \
		$(SRC_FOLDER)/execution/execution.c

OBJS = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))

all: $(OBJ_FOLDER) $(NAME)

v valgrind: all
	valgrind --suppressions=rl.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

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
