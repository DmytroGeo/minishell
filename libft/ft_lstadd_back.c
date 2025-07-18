/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:16:30 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:16:55 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief This function adds the new element 'new'
 *  to the end of the linked list pointed to by 'lst'.
 *  If the list is empty, it sets 'lst' to point to 'new',
// otherwise it traverses to the last element and appends 'new'. 
 * @param lst the address of the pointer to the first element of the list, 
 * @param new a pointer to the new element to be added.
 * @return Nothing (void function).
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
