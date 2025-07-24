/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:13:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/24 12:50:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dlstsize(t_token *tok)
{
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
