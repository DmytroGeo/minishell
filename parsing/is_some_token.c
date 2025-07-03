/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_some_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:42:50 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 11:15:34 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_EOF(t_token *current_token)
{
    return (current_token->type == END_OF_FILE);
}

int is_double_quotes(t_token *current_token)
{
    return (current_token->type == DOUBLE_QUOTED_STRING);
}

int is_single_quotes(t_token *current_token)
{
    return (current_token->type == SINGLE_QUOTED_STRING);
}

int is_variable(t_token *current_token)
{
    return (current_token->type == VARIABLE);
}
            
int is_command(t_token *current_token)
{
    if (!is_EOF(current_token))
    {
        return (is_built_in(current_token->value) || (current_token->path != NULL));
    }
    return (current_token->path != NULL);
}

int is_redir_in(t_token *current_token)
{
    return (current_token->type == REDIR_IN);
}

int is_redir_out(t_token *current_token)
{
    return (current_token->type == REDIR_OUT);
}

int is_file(t_token *current_token)
{
    return (current_token->type == WORD && current_token->path == NULL);
}

int is_pipe(t_token *current_token)
{
    return (current_token->type == PIPE);
}

int is_flag(t_token *current_token)
{
    return (current_token->type == FLAG);   
}

int is_append(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == APPEND);
}

int is_heredoc(t_token *current_token)
{
    return (current_token->type == HEREDOC);
}