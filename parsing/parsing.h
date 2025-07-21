/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:21:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 14:34:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lexing/lexing.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int		is_word(t_token *current_token);
int		is_pipe(t_token *current_token);
int		is_append(t_token *current_token);
int		is_heredoc(t_token *current_token);
int		is_redir_in(t_token *current_token);
int		is_redir_out(t_token *current_token);
int		is_redirect(t_token *current_token);
int		heredoc_fd(char *limiter);
int		is_valid_variable_assignment(char *str);
int		is_valid_variable_name(char *str);
int		find_env_index(char **envp, const char *key);
int		find_number_of_outfiles(t_token *tok_chain);
int		find_number_of_infiles(t_token *tok_chain);
int		find_infiles(t_proc *proc, t_token *start);
int		find_outfiles(t_proc *proc, t_token *tok_chain);
int		find_cmd_and_args(t_proc *proc, t_token *tok_chain, char **envp);
int		return_heredoc_fd(char *limiter);
int		syntax_check_1(t_token *curr);
int		syntax_check_2(t_token *curr);
int		syntax_check_3(t_token *curr);
int		syntax_check_4(t_token *curr);
int		check_syntax(t_token *tok_chain);
int		init_processes(t_cshell *cshell);

void	proc_call(int i, char c);
void	init_cshell(t_cshell *cshell, char **envp);
void	unset_variable(char ***envp, const char *key);
void	export_variable(char ***envp, const char *assignment);
void	do_all_expansions(t_token **tok_chain, int exit_status, char **envp);
void	infile_err2(char *file_name);
void	infile_err3(char *file_name);
void	outfile_err(char *file_name);
void	free_proc_contents(t_proc *proc);

char	**copy_envp(char **envp);
#endif