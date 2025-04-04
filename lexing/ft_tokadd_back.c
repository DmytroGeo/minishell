/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:16:30 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 18:14:45 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	ft_tokadd_back(t_token **tok, t_token *new)
{
	// add token *new to back of list *tok
	t_token	*current;

	if (tok == NULL || new == NULL)
		return ;
	if (*tok == NULL)
	{
		*tok = new;
		return ;
	}
	current = *tok;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
