/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:17:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:03:12 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	// Arguments: t_list *lst – the list element to delete, void (*del)(void*) – a function to delete the content of the element.
	// Returns: Nothing (void function).
	// This function deletes a single element from the linked list by applying the 'del' function to its content and then freeing the memory allocated for the element itself.
	if (!del)
		return ;
	(del)((lst->content));
	free(lst);
}
