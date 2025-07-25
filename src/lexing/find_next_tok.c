/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:32 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 21:40:17 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*find_next_raw_tok(char *line, t_lex *lex)
{
	char	*next_raw_tok;

	next_raw_tok = NULL;
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
		else if (!(lex->in_quotes) && (line[lex->i] == ' ' || is_op_start(line, lex->i)))
		{
			if (lex->start != -1)
				return (function_3(lex, line));
			if (is_op_start(line, lex->i))
				return (function_4(line, lex));		
		}
		else if (lex->start == -1)
			lex->start = lex->i;
		(lex->i)++;
	}
	if (lex->start != -1)
		return (ft_substr(line, lex->start, lex->i - lex->start));
	return (next_raw_tok);
}

char	*find_next_raw_tok(char *line, t_lex *lex)
{
	char	*next_raw_tok;
	int		op_len;

	next_raw_tok = NULL;
	op_len = 0;
	if (lex->i == (int)(ft_strlen(line)))
		return (next_raw_tok);
	while (line[lex->i])
	{
		if ((line[lex->i] == '\'' || line[lex->i] == '"') && !(lex->in_quotes))
		{
			lex->in_quotes = 1;
			lex->current_quote = line[lex->i];
			if (lex->start == -1)
				lex->start = lex->i;
			(lex->i)++;
			continue ;
		}
		else if (lex->in_quotes && line[lex->i] == lex->current_quote)
		{
			(lex->i)++;
			lex->in_quotes = 0;
			continue ;
		}
		else if (!(lex->in_quotes) && (line[lex->i] == ' ' || is_op_start(line, lex->i)))
		{
			if (lex->start != -1)
			{
				next_raw_tok = ft_substr(line, lex->start, lex->i - lex->start);
				lex->start = -1;
				return (next_raw_tok);
			}
			if (is_op_start(line, lex->i))
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

// char	**split_line(char *line)
// {
// 	char	**tokens;
// 	int		token_count;
// 	int		i;
// 	int		start;
// 	int		in_quotes;
// 	char	current_quote;

// 	token_count = 0;
// 	i = 0;
// 	start = -1;
// 	in_quotes = 0;
// 	current_quote = 0;
// 	tokens = ft_calloc(sizeof(char *), 256);
// 	if (!tokens)
// 		return (NULL);
// 	while (line[i])
// 	{
// 		// Handle entering a quote block		
// 		if ((line[i] == '\'' || line[i] == '"') && !in_quotes)
// 		{
// 			in_quotes = 1;
// 			current_quote = line[i];
// 			if (start == -1)
// 				start = i;
// 			i++;
// 			continue ;
// 		}
// 		// Handle closing a quote block
// 		else if (in_quotes && line[i] == current_quote)
// 		{
// 			i++;
// 			in_quotes = 0;
// 			continue ;
// 		}
// 		// Token end (space outside quotes or operator)
// 		else if (!in_quotes && (line[i] == ' ' || is_operator_start(line, i)))
// 		{
// 			if (start != -1)
// 			{
// 				tokens[token_count++] = ft_substr(line, start, i - start);
// 				start = -1;
// 			}
// 			if (is_operator_start(line, i))
// 			{
// 				int op_len = operator_length(line + i);
// 				tokens[token_count++] = ft_substr(line, i, op_len);
// 				i += op_len;
// 				continue ;
// 			}
// 		}
// 		else if (start == -1)
// 			start = i;
// 		i++;
// 	}
// 	if (start != -1)
// 		tokens[token_count++] = ft_substr(line, start, i - start);
// 	return (tokens);
// }
