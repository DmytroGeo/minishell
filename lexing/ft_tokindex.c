/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:03:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 18:13:13 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	ft_tokindex(t_token *elem, t_token **head)
{
	// This function returns the index of the node in token list **head that has the same value attribute as *elem.
	int		index;
	int		value_len;
	t_token	*current;

	if (!elem || !head)
		return (-1);
	index = 0;
	value_len = ft_strlen(elem->value);
	current = *head;
	while (current != NULL)
	{
		if (ft_strncmp(elem->value, current->value, value_len) == 0)
			return (index);
		index++;
		current = current->next;
	}
	return (-1);
}
