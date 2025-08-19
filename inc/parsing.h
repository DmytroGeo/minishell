/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:02:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/19 15:01:59 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structures.h"

int			is_word(t_token *current_token);
int			is_pipe(t_token *current_token);
int			is_append(t_token *current_token);
int			is_heredoc(t_token *current_token);
int			is_redir_in(t_token *current_token);
int			is_redir_out(t_token *current_token);
int			is_redirect(t_token *current_token);
int			is_valid_variable_name(char *str);
int			find_inf_and_outf(t_proc *proc, t_token *start, t_cshell *cshell);
int			find_cmd_and_args(t_proc *proc, t_token *tok_chain, char **envp);
int			syntax_check_1(t_token *curr);
int			syntax_check_2(t_token *curr);
int			syntax_check_3(t_token *curr);
int			syntax_check_4(t_token *curr);
int			check_syntax(t_token *tok_chain);
int			unset_variable(char ***envp, char *key);
int			copy_envp(char ***address_of_copy, char **envp);
int			heredoc_fd(char *limiter, int i, t_cshell *cshell);

void		add_one_char_to_hd_str(t_hd_exp *hd_exp);
void		init_hd_exp(t_hd_exp *hd_exp, char *value);
void		free_hd_exp(t_hd_exp *hd_exp);
void		find_num_inf_and_outf(t_proc *proc, t_token *start);
void		init_cshell(t_cshell *cshell, char **envp);
void		free_proc_contents(t_proc *proc);
void		init_processes(t_cshell *cshell);
void		init_line(char **line, char *prompt);

char		*heredoc_expand(char *str, t_cshell *cshell);

#endif