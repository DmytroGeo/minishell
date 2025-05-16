/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_lstclear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:18:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 13:11:45 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_exec_lstclear(t_exec_list **lst)
{
	t_exec_list	*current;

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
