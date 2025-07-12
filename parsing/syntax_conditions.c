/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_conditions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:17:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 17:36:54 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.c"

int     pre_parsing_condition1(t_token *curr)
{
    return (is_redirect(curr) && !is_word(curr->next));
}

int     pre_parsing_condition2(t_token *curr)
{
    return (is_pipe(curr) && !(curr->previous));
}

int     pre_parsing_condition3(t_token *curr)
{
    return (is_pipe(curr)
        && !(is_word(curr->next) || is_redirect(curr->next)));
}

int     pre_parsing_condition4(t_token *curr)
{
    return (is_pipe(curr) && is_eof(curr));
}
