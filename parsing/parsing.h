/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:21:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:22:44 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../libft/libft.h"
#include "../lexing/lexing.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_simple_command
{
	int **infiles;
	char **address_of_prompt;
	char ***address_of_envp;
	int **outfiles;
	char **commands;
}           t_simple_command;

t_simple_command  *parse(t_token *token_chain);

int		is_command(t_token *current_token);
int		is_file(t_token *current_token);
int		is_pipe(t_token *current_token);
int		is_flag(t_token *current_token);
int		is_append(t_token *current_token);
int		is_heredoc(t_token *current_token);
int		is_EOF(t_token *current_token);
int		is_redir_in(t_token *current_token);
int		is_redir_out(t_token *current_token);
int		proc_call(int i, char c);
int		is_valid_variable_assignment(char *str);
int		is_valid_variable_name(char *str);
int     find_env_index(char **envp, const char *key);
int     is_variable(t_token *current_token);
int 	find_number_of_commands(t_token *token_chain);
int 	find_number_of_outfiles(t_token *token_chain);
int		find_number_of_infiles(t_token *token_chain);

void    find_commands_and_arguments(t_simple_command *simple_command, t_token *token_chain);
void    find_outfiles(t_simple_command *simple_command, t_token *token_chain);
void    find_infiles(t_simple_command *simple_command, t_token *token_chain);
void	unset_variable(char ***envp, const char *key);
void	copy_envp(char ***envp);
void    copy_envp(char ***envp);
void	export_variable(char ***envp, const char *assignment);
void	unset_variable(char ***envp, const char *key);
void    do_all_expansions(t_token **token_chain, int exit_status, char **envp);
void	init_exec_struct_2(t_simple_command *simple_command, t_token *token_chain);

t_simple_command	*init_exec_struct(char *prompt, char **envp);

#endif