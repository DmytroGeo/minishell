/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:24:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 21:38:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	is_op_start(char *line, int i)
{
	if (!line[i])
		return (0);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}

int	operator_length(char *line)
{
	if (!line)
		return (0);
	if ((line[0] == '|' && line[1] == '|')
		|| (line[0] == '>' && line[1] == '>')
		|| (line[0] == '<' && line[1] == '<'))
		return (2);
	return (1);
}

void	function_1(t_lex *lex, char *line)
{
	lex->in_quotes = 1;
	lex->current_quote = line[lex->i];
	if (lex->start == -1)
		lex->start = lex->i;
	(lex->i)++;	
}

void	function_2(t_lex *lex)
{
	(lex->i)++;
	lex->in_quotes = 0;	
}

char	*function_3(t_lex *lex, char *line)
{
	char	*next_raw_tok;

    next_raw_tok = ft_substr(line, lex->start, lex->i - lex->start);
    lex->start = -1;
    return (next_raw_tok);
}

char	*function_4(t_lex *lex, char *line)
{
	int		op_len;
	char	*next_raw_tok;

    op_len = operator_length(line + lex->i);
    next_raw_tok = ft_substr(line, lex->i, op_len);
    lex->i += op_len;
    return (next_raw_tok);
}