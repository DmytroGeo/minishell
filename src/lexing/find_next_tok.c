/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:32 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/27 17:38:04 by dgeorgiy         ###   ########.fr       */
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
	if ((line[0] == '>' && line[1] == '>')
		|| (line[0] == '<' && line[1] == '<'))
		return (2);
	return (1);
}

int	function_3_condition(t_lex *lex, char *line)
{
	return (!(lex->in_quotes)
		&& (line[lex->i] == ' ' || is_op_start(line, lex->i)));
}

int	find_next_raw_tok(char *line, t_lex *lex)
{
	while (line[lex->i])
	{
		if ((line[lex->i] == '\'' || line[lex->i] == '"') && !(lex->in_quotes))
		{
			function_1(lex, line);
			continue ;
		}
		else if (lex->in_quotes && line[lex->i] == lex->current_quote)
		{
			function_2(lex);
			continue ;
		}
		else if (function_3_condition(lex, line))
		{
			if (lex->start != -1 || is_op_start(line, lex->i))
				return (function_3(lex, line));
		}
		else if (lex->start == -1)
			lex->start = lex->i;
		(lex->i)++;
	}
	if (lex->start != -1)
		return (function_4(lex, line));
	return (0);
}
