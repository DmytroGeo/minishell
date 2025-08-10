/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:32 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/09 11:46:43 by dgeorgiy         ###   ########.fr       */
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

int	is_op(t_lex *lex, char *line)
{
	return (!(lex->in_quotes)
		&& (line[lex->i] == ' ' || is_op_start(line, lex->i)));
}

/**
 * @param line the line read returned from (from readline)
 * @param lex the lex structure, used to keep track of where we are in the
 * line, whether we're in quotes or not
 * @return 0 when complete, -42 in case of memory allocation fail.
 * @brief This function goes through the line returned from readline
 * and finds the next raw token (word or operator), and saves it in the
 * char *next_raw_tok attribute of lex, to be used to initialise a token in
 * the lexing() function. Since lex is declared in the lexing.c and passed by
 * address to this function it saves where we are in the string between
 * function calls so every time the function is called it gets updated
 * with the next raw token.
 */
int	find_next_raw_tok(char *line, t_lex *lex)
{
	while (line[lex->i])
	{
		if ((line[lex->i] == '\'' || line[lex->i] == '"') && !(lex->in_quotes))
		{
			start_quotes(lex, line);
			continue ;
		}
		else if (lex->in_quotes && line[lex->i] == lex->current_quote)
		{
			inside_quotes(lex);
			continue ;
		}
		else if (is_op(lex, line))
		{
			if (lex->start != -1 || is_op_start(line, lex->i))
				return (return_op(lex, line));
		}
		else if (lex->start == -1)
			lex->start = lex->i;
		(lex->i)++;
	}
	if (lex->start != -1)
		return (return_rest_of_line(lex, line));
	return (0);
}
