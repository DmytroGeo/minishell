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

# include "lexing.h"

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