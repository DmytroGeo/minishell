/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:28:57 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:23 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

t_list	*ft_find_node(int i, t_list **head)
{
	t_list	*temp;

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
