/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:56 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:06:08 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	// Arguments: void *content – the content to store in the new list element.
	// Returns: A pointer to the newly created list element, or NULL if memory allocation fails.
	// This function creates a new list element, initializes its content to the given 'content', sets its 'next' pointer to NULL, and returns a pointer to the new node.
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
