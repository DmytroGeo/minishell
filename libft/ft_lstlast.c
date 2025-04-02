/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:15:34 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:04:50 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	// Arguments: t_list *lst – the linked list to search through.
	// Returns: The last element of the list, or NULL if the list is empty.
	// This function iterates through the linked list until it finds the last element (the one whose 'next' pointer is NULL) and returns it.
	t_list	*current;

	current = lst;
	if (lst == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}
