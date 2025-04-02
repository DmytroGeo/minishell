/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:12:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:01:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	// Arguments: t_list **lst – a pointer to the pointer to the first element of the list, t_list *new – a pointer to the new element to be added.
	// Returns: Nothing (void function).
	// This function adds the new element 'new' at the beginning of the linked list pointed to by 'lst'. It sets the 'next' pointer of 'new' to point to the current first element, then updates 'lst' to point to 'new'.
	new->next = *lst;
	*lst = new;
}
