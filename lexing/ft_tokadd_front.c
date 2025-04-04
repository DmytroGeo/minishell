/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:12:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 18:14:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	ft_tokadd_front(t_token **tok, t_token *new)
{
	// add token *new to front of list *tok
	new->next = *tok;
	*tok = new;
}
