/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:04:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:51:05 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "structures.h"

void		lexing(t_cshell *cshell, char *line);
void		ft_dlstadd_back(t_token **head, t_token *tok);
void		ft_dlstadd_front(t_token **head, t_token *tok);
void		print_raw_tokens(char **raw_tokens);
void		print_token_list(t_token *head);
void		populate_operators(t_op *operators);
void		ft_perror(char *str, char c);
void		del_tok_cont(void *content);
void		free_tok_chain(t_token **start, void (*del)(void*));
void		free_cshell(t_cshell *cshell);
void		free_whole_cshell(t_cshell *cshell);
void		free_proc_array(t_proc *proc_array, int len);

int			is_surrounded_by(char *str, char quote);
int			is_operator_start(char *line, int i);
int			operator_length(char *line);
int			ft_tokindex(t_token *elem, t_token **head);
int			ft_toksize(t_token *tok);

t_token		*ft_toklast(t_token *tok);
t_token		*ft_dlstnew(void *content);

t_tok_type	identify_type(char *token, t_op *operators);

t_tok_cont	*init_tok_cont(char *raw_token, t_op *operators);

char		*find_variable_in_envp(char **envp, char *variable);
char		*strip_quotes(char *str);
char		*get_path(char *str, char **envp);
char        *find_next_raw_tok(char *line, t_lex *lex);
#endif