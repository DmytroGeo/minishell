/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:19:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:04:00 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	// Arguments: t_list *lst – the linked list to iterate through, void (*f)(void*) – a function to apply to each element's content.
	// Returns: Nothing (void function).
	// This function iterates through each element of the linked list and applies the function 'f' to the content of each element.
	if (lst == NULL || !f)
		return ;
	while (lst != NULL)
	{
		(f)(lst->content);
		lst = lst->next;
	}
}
