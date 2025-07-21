/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:17:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 13:32:04 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @param lst The list element to delete.
 * @param del – A function to delete the content of the element.
 * @return Nothing (void function).
 * @brief This function deletes a single element from the linked list
 * by applying the 'del' function to its content
 * and then freeing the memory allocated for the element itself.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	(del)((lst->content));
	free(lst);
}
