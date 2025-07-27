/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:24:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/27 17:36:13 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

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

int	function_3(t_lex *lex, char *line)
{
	int	op_len;

	if (lex->start != -1)
	{
		lex->next_raw_tok = ft_substr(line, lex->start, lex->i - lex->start);
		if (!(lex->next_raw_tok))
			return (-42);
		lex->start = -1;
		return (0);
	}
	if (is_op_start(line, lex->i))
	{
		op_len = operator_length(line + lex->i);
		lex->next_raw_tok = ft_substr(line, lex->i, op_len);
		if (!(lex->next_raw_tok))
			return (-42);
		lex->i += op_len;
		return (0);
	}
	return (0);
}

int	function_4(t_lex *lex, char *line)
{
	lex->next_raw_tok = ft_substr(line, lex->start, lex->i - lex->start);
	if (!lex->next_raw_tok)
		return (-42);
	return (0);
}
