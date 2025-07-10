/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/09 10:57:38 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	populate_operators(t_op *operators)
{
    operators[0] = (t_op){"|", _pipe};
    operators[1] = (t_op){">", redir_out};
    operators[2] = (t_op){"<", redir_in};
    operators[3] = (t_op){">>", append};
    operators[4] = (t_op){"<<", heredoc};
    operators[5] = (t_op){NULL, word};
    operators[6] = (t_op){NULL, end_of_file};
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
    // print_raw_tokens(raw_tokens);
    while (*raw_tokens)
    {
        new_node = malloc(sizeof(t_token));
        if (!new_node)
            return (NULL);
		else
		{
			new_node->value = ft_strdup(*raw_tokens);
			new_node->type = identify_type(*raw_tokens, operators);
		}
        new_node->next = NULL;
        new_node->path = NULL;
        // if (new_node->type == WORD && (!last || last->type == PIPE))
        if (new_node->type == word)
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
	new_node->type = end_of_file;
	new_node->next = NULL;
	new_node->path = NULL;
	last->next = new_node;
	last = new_node;
    // print_token_list(head);
    return (head);
}
