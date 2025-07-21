/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:12:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 11:48:17 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	ft_dlstadd_front(t_token **tok, t_token *new)
{
	new->next = *tok;
	(*tok)->previous = new;
	*tok = new;
}
