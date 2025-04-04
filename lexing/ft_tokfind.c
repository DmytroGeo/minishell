/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:46:57 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 17:01:37 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_token	*ft_tokfind(int i, t_token **head)
{
	// This function finds the ith element in the token list 'head' and returns a pointer to it.
	// We start our count from 0 to avoid one-off errors. So the first token has index 0, the nth token has index n-1. 
	t_token	*current;

	current = *head;
	if (!head || !*head || i >= ft_toksize(*head))
		return (NULL);
	while (current != NULL && current->index != i)
		current = current->next;
	return (current);
}