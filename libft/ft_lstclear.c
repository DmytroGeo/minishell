/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:18:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:39:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @param lst The address of a the pointer to the first element of the list.
 * @param del A function to delete the content of each element.
 * @return Nothing (void function).
 * @brief This function clears the entire linked list,
 * applying the 'del' function to each element's content
 * before freeing the memory for the element itself,
 * and sets 'lst' to NULL after clearing.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
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
