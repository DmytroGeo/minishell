/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toksize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:13:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 18:18:22 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	ft_toksize(t_token *tok)
{
	// Arguments: t_list *tok – the linked list to count the elements of.
	// Returns: The number of elements in the linked list.
	int		count;
	t_token	*current;

	count = 0;
	current = tok;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
