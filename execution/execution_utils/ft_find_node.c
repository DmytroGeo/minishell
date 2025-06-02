/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:28:57 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/31 17:08:57 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
		if (((t_execution_content *)(temp->content))->index == i)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}
