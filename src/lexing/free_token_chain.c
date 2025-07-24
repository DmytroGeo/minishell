/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tok_chain.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:06:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 12:47:02 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param start The address of the pointer to the first element of the list.
 * @param del A function to delete the content of each element.
 * @return Nothing (void function).
 * @brief This function frees the entire doubly-linked list,
 * applying the 'del' (content freeing) function to each element's content
 * before freeing the memory for the element itself,
 * and sets 'lst' to NULL after clearing.
 */
void	free_tok_chain(t_token **start, void (*del)(void*))
{
	t_token	*current;

	current = *start;
	if (current == NULL || !del)
		return ;
	while (current != NULL)
	{
		*start = current->next;
		(del)(current->content);
		free(current);
		current = *start;
	}
}
