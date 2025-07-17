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
	if ((line[0] == '|' && line[1] == '|') ||
		(line[0] == '>' && line[1] == '>') ||
		(line[0] == '<' && line[1] == '<'))
		return (2);
	return (1);
}

char	**split_line(char *line)
{
	char	**tokens = malloc(sizeof(char *) * 256); // malloc not accounted for
	int		token_count = 0;
	int		i = 0;
	int		start = -1;
	int		in_quotes = 0;
	char	current_quote = 0;

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
			continue;
		}
		// Handle closing a quote block
		else if (in_quotes && line[i] == current_quote)
		{
			i++;
			in_quotes = 0;
			continue;
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
				continue;
			}
		}
		else if (start == -1)
			start = i;
		i++;
	}

	if (start != -1)
		tokens[token_count++] = ft_substr(line, start, i - start);
	tokens[token_count] = NULL;
	return (tokens);
}
