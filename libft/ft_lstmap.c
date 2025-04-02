/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:19:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:05:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	// Arguments: t_list *lst – the linked list to iterate through, void *(*f)(void*) – a function to apply to each element's content, void (*del)(void*) – a function to delete content if memory allocation fails.
	// Returns: A new linked list with the transformed content, or NULL if memory allocation fails or input is invalid.
	// This function applies the function 'f' to each element of the original list to create a new list with transformed content, and uses 'del' to clean up in case of failure.
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew((*f)(lst->content));
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
