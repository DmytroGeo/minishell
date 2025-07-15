/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:16:30 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/14 13:46:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	ft_dlstadd_back(t_token **address_of_head, t_token *new)
{
	t_token	*current;

	if (address_of_head == NULL || new == NULL)
		return ;
	if (*address_of_head == NULL)
	{
		*address_of_head = new;
		return ;
	}
	current = *address_of_head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->previous = current;
}
