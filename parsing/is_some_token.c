/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_some_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:42:50 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:24:00 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_EOF(t_token *current_token)
{
    return (current_token->type == END_OF_FILE);
}

int is_variable(t_token *current_token)
{
        return (current_token->type == VARIABLE);
}

int is_file(t_token *current_token)
{
    return (current_token->type == WORD && current_token->path == NULL);
}

int is_pipe(t_token *current_token)
{
    return (current_token->type == PIPE);
}