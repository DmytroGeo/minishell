/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 20:09:58 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include <stdio.h> // remove later
#include <string.h> // remove later

void	print_token_list(t_token *head)
{
	int	i;
	const char *token_type_names[] = 
	{
    "WORD",
    "PIPE",
    "REDIR_IN",
    "REDIR_OUT",
    "APPEND",
    "HEREDOC"
	};

	i = 1;
	printf("\n< < < < Token List > > > >\n\n");
	while (head)
	{
		printf("Node : %d\n", i);
		printf("Type : %s\nValue : %s\n\n", token_type_names[head->type], head->value);
		head = (head->next);
		i++;
	}
	printf("\n");
}

t_token_type identify_type(char *token, t_op *operators) //include?
{
	int	i;

	i = 0;
	while (operators[i].symbol)
	{
		if (strcmp(token, operators[i].symbol) == 0) // change strcmp
			return (operators[i].type);
		i++;
	}
	return (WORD);
}

void	print_raw_tokens(char **raw_tokens) //include? 
{
	int	i;

	i = 0;
	printf("\n\n< < < < Raw Tokens > > > >\n\n"); // replace
	while (raw_tokens[i])
			printf("%s\n", raw_tokens[i++]); // replace
	printf("\n");  // replace
}

t_token		*lexing(char *line)
{
	char	**raw_tokens;
	t_op	operators[6];
	t_token *head = NULL;
	t_token *new_node;

	operators[0] = (t_op){"|", PIPE};
	operators[1] = (t_op){">", REDIR_OUT};
	operators[2] = (t_op){"<", REDIR_IN};
	operators[3] = (t_op){">>", APPEND};
	operators[4] = (t_op){"<<", HEREDOC};
	operators[5] = (t_op){NULL, WORD};
	if (!line)
		return (NULL);
	raw_tokens = ft_split(line, ' ');
	print_raw_tokens(raw_tokens);
	while (*raw_tokens)
	{
		new_node = ft_toknew(identify_type(*raw_tokens, operators), *raw_tokens, 1);
		if (!new_node)
			return (NULL);
		raw_tokens++;
		//finnish with dimas functions.
	}

	print_token_list(head);
	return (head);
}
