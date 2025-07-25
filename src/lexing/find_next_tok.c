/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:32 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:59:12 by dgeorgiy         ###   ########.fr       */
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
		if ((line[*i] == '\'' || line[*i] == '"') && !in_quotes)
		{
			in_quotes = 1;
			current_quote = line[*i];
			if (start == -1)
				start = *i;
			(*i)++;
			continue ;
		}
		else if (in_quotes && line[*i] == current_quote)
		{
			(*i)++;
			in_quotes = 0;
			continue ;
		}
		else if (!in_quotes && (line[*i] == ' ' || is_operator_start(line, *i)))
		{
			if (start != -1)
			{
				next_raw_tok = ft_substr(line, start, *i - start);
				start = -1;
				// move i along;
				return (next_raw_tok);
			}
			if (is_operator_start(line, *i))
			{
				op_len = operator_length(line + *i);
				next_raw_tok = ft_substr(line, *i, op_len);
				*i += op_len;
				return (next_raw_tok);
			}
		}
		else if (start == -1)
			start = *i;
		(*i)++;
	}
	if (start != -1)
		next_raw_tok = ft_substr(line, start, *i - start);
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
