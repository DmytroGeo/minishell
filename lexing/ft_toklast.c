/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toklast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:15:34 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 18:17:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_token	*ft_toklast(t_token *tok)
{
	// Arguments: t_list *tok – the linked list to search through.
	// Returns: The last element of the list, or NULL if the list is empty.
	// This function iterates through the token list until it finds the last element (the one whose 'next' pointer is NULL) and returns it.
	t_token	*current;

	current = tok;
	if (tok == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}
