/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tok_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:13:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 15:33:43 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void  	del_tok_cont(void *content)
{
    t_token_content *token_content;

    token_content = (t_token_content *)content;
    free(token_content->value);
    free(token_content);
}

// void  	del_tok_cont(t_token_content *token_content)
// {
//     free(token_content->value);
//     free(token_content);
//     return ;
// }