/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tok_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:13:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/16 14:01:54 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void  	del_tok_cont(void *content)
{
    t_token_content *token_content;

    token_content = (t_token_content *)content;
    free(token_content->value);
    free(token_content);
}