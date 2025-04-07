/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:17:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/05 12:11:54 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	ft_tokdelone(t_token *tok)
{
	// Arguments: t_list *tok – the list element to delete.
	// Returns: Nothing (void function).
	// This function deletes a single token node. Be careful not to get dangling pointers if using in the middle of a list.
	free(tok->value);
	free(tok);
}
