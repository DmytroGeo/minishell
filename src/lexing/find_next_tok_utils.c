/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:24:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/05 17:46:16 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	start_quotes(t_lex *lex, char *line)
{
	lex->in_quotes = 1;
	lex->current_quote = line[lex->i];
	if (lex->start == -1)
		lex->start = lex->i;
	(lex->i)++;
}

void	inside_quotes(t_lex *lex)
{
	(lex->i)++;
	lex->in_quotes = 0;
}

int	return_op(t_lex *lex, char *line)
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

int	return_rest_of_line(t_lex *lex, char *line)
{
	lex->next_raw_tok = ft_substr(line, lex->start, lex->i - lex->start);
	if (!lex->next_raw_tok)
		return (-42);
	return (0);
}
