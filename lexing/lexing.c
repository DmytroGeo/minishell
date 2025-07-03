/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 10:49:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include <stdio.h> // remove later
#include <string.h> // remove later

void	populate_operators(t_op *operators)
{
    operators[0] = (t_op){"|", PIPE};
    operators[1] = (t_op){">", REDIR_OUT};
    operators[2] = (t_op){"<", REDIR_IN};
    operators[3] = (t_op){">>", APPEND};
    operators[4] = (t_op){"<<", HEREDOC};
    operators[5] = (t_op){NULL, WORD};
    operators[6] = (t_op){NULL, END_OF_FILE};
}

t_token     *lexing(char *line, char **envp)
{
    char    **raw_tokens;
    t_op    operators[7];
    t_token *head = NULL;
    t_token *last;
	populate_operators(operators);
    t_token *new_node;
    if (!line)
        return (NULL);
    raw_tokens = split_line(line);
    print_raw_tokens(raw_tokens);
    while (*raw_tokens)
    {
        new_node = malloc(sizeof(t_token));
        if (!new_node)
            return (NULL);
        if (is_surrounded_by(*raw_tokens, '\''))
		{
			new_node->value = strip_quotes(*raw_tokens);
			new_node->type = SINGLE_QUOTED_STRING;
		}
		else if (is_surrounded_by(*raw_tokens, '"'))
		{
			new_node->value = strip_quotes(*raw_tokens);
			new_node->type = DOUBLE_QUOTED_STRING;
		}
		else
		{
			new_node->value = ft_strdup(*raw_tokens);
			new_node->type = identify_type(*raw_tokens, operators);
		}
        new_node->next = NULL;
        new_node->path = NULL;
        // if (new_node->type == WORD && (!last || last->type == PIPE))
        if (new_node->type == WORD)
        {
            if (access(new_node->value, F_OK | X_OK) == 0)
                new_node->path = ft_strdup(new_node->value);
            else
                new_node->path = get_path(new_node->value, envp);
        }
        if (!head)
            head = new_node;
        else
            last->next = new_node;
        last = new_node;
        raw_tokens++;
    }
    new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = NULL;
	new_node->type = END_OF_FILE;
	new_node->next = NULL;
	new_node->path = NULL;
	last->next = new_node;
	last = new_node;
    print_token_list(head);
    return (head);
}
