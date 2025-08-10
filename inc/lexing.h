/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:04:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/09 11:50:49 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "structures.h"

void		lexing(t_cshell *cshell);
void		ft_dlstadd_back(t_token **head, t_token *tok);
void		populate_operators(t_op *operators);
void		start_quotes(t_lex *lex, char *line);
void		function_2(t_lex *lex);
void		inside_quotes(t_lex *lex);

int			wrong_number_of_quotes(t_cshell *cshell);
int			is_operator_start(char *line, int i);
int			operator_length(char *line);
int			ft_tokindex(t_token *elem, t_token **head);
int			ft_toksize(t_token *tok);
int			is_op_start(char *line, int i);
int			operator_length(char *line);
int			find_next_raw_tok(char *line, t_lex *lex);
int			return_op(t_lex *lex, char *line);
int			return_rest_of_line(t_lex *lex, char *line);

t_token		*ft_toklast(t_token *tok);
t_token		*ft_dlstnew(void *content);

t_tok_type	identify_type(char *token, t_op *operators);

t_tok_cont	*init_tok_cont(char *raw_token, t_op *operators);

char		*strip_quotes(char *str);

#endif