/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toknew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:56 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 19:27:10 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_token	*ft_toknew(char *type, char *value, int index)
{
	// Arguments: void *content – the content to store in the new list element.
	// Returns: A pointer to the newly created list element, or NULL if memory allocation fails.
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->value = value;
	new_node->index = index;
	new_node->next = NULL;
	return (new_node);
}
