/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:18:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:02:21 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	// Arguments: t_list **lst – a pointer to the pointer to the first element of the list, void (*del)(void*) – a function to delete the content of each element.
	// Returns: Nothing (void function).
	// This function clears the entire linked list, applying the 'del' function to each element's content before freeing the memory for the element itself, and sets 'lst' to NULL after clearing.
	t_list	*current;

	current = *lst;
	if (current == NULL || !del)
		return ;
	while (current != NULL)
	{
		*lst = current->next;
		(del)(current->content);
		free(current);
		current = *lst;
	}
}
