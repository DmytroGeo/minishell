/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:06:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/28 19:02:38 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_execution_content *ft_init_content(char *pa, char **fl, int number_of_commands, char **envp)
{
	t_execution_content	*new_node;

	new_node = malloc(sizeof(t_execution_content));
	if (new_node == NULL)
		return (NULL);
	new_node->path = pa;
	new_node->flags = fl;
	new_node->number_of_commands = number_of_commands;
	new_node->index = 0;
	new_node->envp = envp;
	return (new_node);
}