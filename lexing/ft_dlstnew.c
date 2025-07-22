/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:38:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/22 08:51:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

/**
 * @brief This function creates a new doubly-linked list element,
 * initializes its content to the given 'content',
 * sets its 'next' pointer to NULL, and returns a pointer to the new node.
 * @param content The content to store in the new list element.
 * @return A pointer to the newly created list element,
 *  or NULL if memory allocation fails.
 */
t_token	*ft_dlstnew(void *content)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
    new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}