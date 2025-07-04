/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:21:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 16:14:52 by dgeorgiy         ###   ########.fr       */
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
    int *exit_code;
    int **outfiles;
    char **commands;
}           t_simple_command;

t_simple_command  *parse(t_token *token_chain);

int		is_command(t_token *current_token);
int		proc_call(int i, char c);
int		is_EOF(t_token *current_token);
int		is_redir_in(t_token *current_token);
int		is_redir_out(t_token *current_token);
void	unset_variable(char ***envp, const char *key);
void	copy_envp(char ***envp);
int     find_env_index(char **envp, const char *key);
void    copy_envp(char ***envp);
void	export_variable(char ***envp, const char *assignment);
int		is_valid_variable_name(char *str);
void	export_variable(char ***envp, const char *assignment);
int		is_valid_variable_assignment(char *str);
void	unset_variable(char ***envp, const char *key);
int		find_env_index(char **envp, const char *key);
void	print_env(int fd, char **envp);
void	ft_print_envp(char **envp);
int		is_file(t_token *current_token);
int		is_pipe(t_token *current_token);
int		is_flag(t_token *current_token);
int		is_append(t_token *current_token);
int		is_heredoc(t_token *current_token);
void    do_all_expansions(t_token **token_chain, int exit_status, char **envp);
int     is_variable(t_token *current_token);
int     is_single_quotes(t_token *current_token);
int     is_double_quotes(t_token *current_token);

#endif