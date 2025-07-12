/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 18:12:38 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void    populate_operators(t_op *operators)
{
    operators[0] = (t_op){"|", _pipe};
    operators[1] = (t_op){">", redir_out};
    operators[2] = (t_op){"<", redir_in};
    operators[3] = (t_op){">>", append};
    operators[4] = (t_op){"<<", heredoc};
    operators[5] = (t_op){NULL, word};
}

t_token     *lexing(char *line, char **envp)
{
    char    **raw_tokens;
    t_op    operators[6];
    t_token *head;
    t_token *new_token;
    t_token_content *new_content;
    
    head = NULL;
    if (!line)
        return (NULL);
    populate_operators(operators);
    raw_tokens = split_line(line);
    // print_raw_tokens(raw_tokens);
    while (*raw_tokens)
    {
        new_content = init_token_content(*raw_tokens, operators);
        if (!new_content)
        {
            // free list up to this point
            return (NULL);            
        }
        new_token = ft_dlstnew(new_content);
        if (!new_content)
        {
            // free list up to this point
            return (NULL);            
        }        
        ft_dlstadd_back(&head, new_token);
        raw_tokens++;
    }
    // print_token_list(head);
    return (head);
}
