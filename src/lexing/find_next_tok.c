/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:32 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 17:18:36 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	is_operator_start(char *line, int i)
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

char	*find_next_raw_tok(char *line, t_lex *lex)
{
	char	*next_raw_tok;
	int		op_len;

	next_raw_tok = NULL;
	op_len = 0;
	while (line[lex->i])
	{
		// Handle entering a quote block
		if ((line[lex->i] == '\'' || line[lex->i] == '"') && !(lex->in_quotes))
		{
			lex->in_quotes = 1;
			lex->current_quote = line[lex->i];
			if (lex->start == -1)
				lex->start = lex->i;
			(lex->i)++;
			continue ;
		}
		// Handle closing a quote block
		else if (lex->in_quotes && line[lex->i] == lex->current_quote)
		{
			lex->i++;
			lex->in_quotes = 0;
			continue ;
		}
		// Token end (space outside quotes or operator)
		else if (!(lex->in_quotes) && (line[lex->i] == ' ' || is_operator_start(line, lex->i)))
		{
			if (lex->start != -1)
			{
				next_raw_tok = ft_substr(line, lex->start, lex->i - lex->start);
				lex->start = -1;
				return (next_raw_tok);
			}
			if (is_operator_start(line, lex->i))
			{
				op_len = operator_length(line + lex->i);
				next_raw_tok = ft_substr(line, lex->i, op_len);
				lex->i += op_len;
				return (next_raw_tok);
			}
		}
		else if (lex->start == -1)
			lex->start = lex->i;
		(lex->i)++;
	}
	if (lex->start != -1)
	{
		next_raw_tok = ft_substr(line, lex->start, lex->i - lex->start);
		return (next_raw_tok);	
	}
	return (next_raw_tok);
}

char	**split_line(char *line)
{
	char	**tokens;
	int		token_count;
	int		i;
	int		start;
	int		in_quotes;
	char	current_quote;

	token_count = 0;
	i = 0;
	start = -1;
	in_quotes = 0;
	current_quote = 0;
	tokens = ft_calloc(sizeof(char *), 256);
	if (!tokens)
		return (NULL);
	while (line[i])
	{
		// Handle entering a quote block		
		if ((line[i] == '\'' || line[i] == '"') && !in_quotes)
		{
			in_quotes = 1;
			current_quote = line[i];
			if (start == -1)
				start = i;
			i++;
			continue ;
		}
		// Handle closing a quote block
		else if (in_quotes && line[i] == current_quote)
		{
			i++;
			in_quotes = 0;
			continue ;
		}
		// Token end (space outside quotes or operator)
		else if (!in_quotes && (line[i] == ' ' || is_operator_start(line, i)))
		{
			if (start != -1)
			{
				tokens[token_count++] = ft_substr(line, start, i - start);
				start = -1;
			}
			if (is_operator_start(line, i))
			{
				int op_len = operator_length(line + i);
				tokens[token_count++] = ft_substr(line, i, op_len);
				i += op_len;
				continue ;
			}
		}
		else if (start == -1)
			start = i;
		i++;
	}
	if (start != -1)
		tokens[token_count++] = ft_substr(line, start, i - start);
	return (tokens);
}
