/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:21:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 18:21:02 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../libft/libft.h"
#include "../lexing/lexing.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_proc_struct
{
	int **infiles; // this is an array of integer pointers so that I can null-terminate it. I like dealing with NULL-terminated arrays
	int **outfiles;
	char **cmd_and_args;
}           t_proc;

typedef struct s_big_struct
{
	char *prompt;
	char **envp;
	int	num_of_proc;
	t_proc *proc_array;	
}           t_big_struct;

t_proc  *parse(t_token *token_chain);

int 	is_word(t_token *current_token);
int		is_pipe(t_token *current_token);
int		is_append(t_token *current_token);
int		is_heredoc(t_token *current_token);
int		is_eof(t_token *current_token);
int		is_redir_in(t_token *current_token);
int		is_redir_out(t_token *current_token);
int		is_redirect(t_token *current_token);


int		proc_call(int i, char c);
int		is_valid_variable_assignment(char *str);
int		is_valid_variable_name(char *str);
int     find_env_index(char **envp, const char *key);

int 	find_number_of_outfiles(t_token *token_chain);
int		find_number_of_infiles(t_token *token_chain);
int		find_infiles(t_proc *process, t_token *start);
int		find_outfiles(t_proc *process, t_token *token_chain);

int     pre_parsing_condition1(t_token *curr);
int     pre_parsing_condition1(t_token *curr);
int     pre_parsing_condition1(t_token *curr);
int     pre_parsing_condition1(t_token *curr);
int		find_command_and_arguments(t_proc *simple_command, t_token *token_chain, char **envp);

void	unset_variable(char ***envp, const char *key);
void	export_variable(char ***envp, const char *assignment);
void	unset_variable(char ***envp, const char *key);
void    do_all_expansions(t_token **token_chain, int exit_status, char **envp);
void	init_processes(t_big_struct *big_struct, t_token *token_chain);
char	**copy_envp(char **envp);
int		return_heredoc_fd(char *limiter);
int		init_envp_and_prompt(t_big_struct *big_struct, char **envp);


void	outfile_err(char *str);
#endif