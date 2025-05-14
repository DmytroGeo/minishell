/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:18:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*current;

	current = *lst;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		*lst = current->next;
		free(current->path);
		ft_array_free(current->flags);
		free(current);
		current = *lst;
	}
}
