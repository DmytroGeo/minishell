/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:18:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 16:18:47 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	ft_tokclear(t_token **tok)
{
	t_token	*current;

	current = *tok;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		*tok = current->next;
		ft_tokdelone(current);
		current = *tok;
	}
}
