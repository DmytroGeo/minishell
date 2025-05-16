/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:26:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 13:09:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_exec_list	*ft_exec_lstnew(char *pa, char **fl, int ac, char **envp)
{
	t_exec_list	*new_node;

	new_node = malloc(sizeof(t_exec_list));
	if (!new_node)
		return (NULL);
	new_node->path = pa;
	new_node->flags = fl;
	new_node->next = NULL;
	new_node->ac = ac;
	new_node->index = 0;
	new_node->av = NULL;
	new_node->envp = envp;
	return (new_node);
}
