/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:08:32 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/24 18:38:15 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
