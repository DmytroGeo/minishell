/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:16:30 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:13:08 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
/**
 * @brief This function adds the new element 'new'
 *  to the end of the doubly-linked list pointed to by 'lst'.
 *  If the list is empty, it sets 'lst' to point to 'new',
// otherwise it traverses to the last element and appends 'new'. 
 * @param lst the address of the pointer to the first element of the list, 
 * @param new a pointer to the new element to be added.
 * @return Nothing (void function).
 */
void	ft_dlstadd_back(t_token **address_of_head, t_token *new)
{
	t_token	*current;

	if (address_of_head == NULL || new == NULL)
		return ;
	if (*address_of_head == NULL)
	{
		*address_of_head = new;
		return ;
	}
	current = *address_of_head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->previous = current;
}
