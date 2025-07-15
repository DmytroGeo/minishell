/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:21:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 16:57:56 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../lexing/lexing.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_proc
{
	int num_inf;
	int num_outf;
	int *infiles;
	int *outfiles;
	char **cmd_and_args;
}           t_proc;

typedef struct s_main
{
	char *prompt;
	char **envp;
	int	num_of_proc;
	t_proc *proc_array;	
}           t_main;

t_proc  *parse(t_token *tok_chain);

int 	is_word(t_token *current_token);
int		is_pipe(t_token *current_token);
int		is_append(t_token *current_token);
int		is_heredoc(t_token *current_token);
int		is_eof(t_token *current_token);
int		is_redir_in(t_token *current_token);
int		is_redir_out(t_token *current_token);
int		is_redirect(t_token *current_token);
int		heredoc_fd(char *limiter);
int		proc_call(int i, char c);
int		is_valid_variable_assignment(char *str);
int		is_valid_variable_name(char *str);
int		find_env_index(char **envp, const char *key);
int 	find_number_of_outfiles(t_token *tok_chain);
int		find_number_of_infiles(t_token *tok_chain);
int		find_infiles(t_proc *process, t_token *start);
int		find_outfiles(t_proc *process, t_token *tok_chain);
int		find_cmd_and_args(t_proc *simple_command, t_token *tok_chain, char **envp);
int		return_heredoc_fd(char *limiter);
void	init_envp_and_prompt(t_main *main, char **envp);
int     syntax_check_1(t_token *curr);
int     syntax_check_2(t_token *curr);
int     syntax_check_3(t_token *curr);
int     syntax_check_4(t_token *curr);

int		check_syntax(t_token *tok_chain);

void	unset_variable(char ***envp, const char *key);
void	export_variable(char ***envp, const char *assignment);
void    do_all_expansions(t_token **tok_chain, int exit_status, char **envp);
void	init_processes(t_main *main, t_token *tok_chain);
void    free_tok_chain(t_token **start, void (*del)(void*));
void  	del_tok_cont(void *content);
void	infile_err2(char *file_name);
void	infile_err3(char *file_name);
void	outfile_err(char *file_name);
void	free_main(t_main *main);

char	**copy_envp(char **envp);
#endif