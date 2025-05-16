/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:28:57 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 13:08:12 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_exec_list	*ft_find_node(int i, t_exec_list **head)
{
	t_exec_list	*temp;

	if (!head)
		return (NULL);
	temp = *head;
	if (!temp)
		return (NULL);
	while (temp)
	{
		if (temp->index == i)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}
