/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tok_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:13:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/22 08:58:10 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
/**
 * @param content The address of the pointer to the first element of the list.
 * @return Nothing (void function).
 * @brief This function is the 'del' function that is passed 
 * to the function 'free_tok_chain', which actually frees the 
 * content (in this case the char *value).
 */
void  	del_tok_cont(void *content)
{
    t_token_content *token_content;

    token_content = (t_token_content *)content;
    free(token_content->value);
    free(token_content);
}