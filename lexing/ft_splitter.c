#include "lexing.h"

int	is_operator_start(char *line, int i)
{
	if (!line[i])
		return (0);
	if (line[i] == '|' || line[i] == '&' || line[i] == '<' ||
		line[i] == '>' || line[i] == '(' || line[i] == ')')
		return (1);
	return (0);
}

int	operator_length(char *line)
{
	if (!line)
		return (0);
	if ((line[0] == '&' && line[1] == '&') ||
		(line[0] == '|' && line[1] == '|') ||
		(line[0] == '>' && line[1] == '>') ||
		(line[0] == '<' && line[1] == '<'))
		return (2);
	return (1);
}

char	**split_line(char *line)
{
	char	**tokens;
	int		i = 0;
	int		token_count = 0;
	int		start = -1;
	int		inside_single_quotes = 0;
	int		inside_double_quotes = 0;

	tokens = malloc(sizeof(char *) * 256);
	if (!tokens)
		return (NULL);

	while (line[i])
	{
		if (line[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (line[i] == '"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		// Handle space or operator (only outside of quotes)
		else if ((line[i] == ' ' || is_operator_start(line, i)) &&
				!inside_single_quotes && !inside_double_quotes)
		{
			// Finish the current token if we were building one
			if (start != -1)
			{
				tokens[token_count++] = ft_substr(line, start, i - start);
				start = -1;
			}
			// Handle the operator itself as a separate token
			if (is_operator_start(line, i))
			{
				int op_len = operator_length(line + i);
				tokens[token_count++] = ft_substr(line, i, op_len);
				i += op_len - 1; // skip past operator
			}
		}
		// Start a new token if needed
		else if (start == -1)
			start = i;

		i++;
	}
	// Handle any final token at the end of line
	if (start != -1)
		tokens[token_count++] = ft_substr(line, start, i - start);

	tokens[token_count] = NULL; // Null-terminate the tokens array
	return (tokens);
}
