/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 13:00:22 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute(int i, int **fd, int *pid, t_exec_list **head)
{
	char	**array;
	t_exec_list	*node;
	int		n;

	node = ft_find_node(i, head);
	array = malloc((2 + ft_array_len(node->flags)) * sizeof(char *));
	if (!array)
		return ;
	array[0] = node->path;
	if (!array[0])
	{
		ft_array_free(array);
		free_and_exit(pid, fd, head);
		exit (127);
	}
	n = 0;
	while (++n <= ft_array_len(node->flags))
		array[n] = (node->flags)[n - 1];
	array[n] = NULL;
	if (execve(node->path, array, (*head)->envp) < 0)
	{
		ft_array_free(array);
		free_and_exit(pid, fd, head);
		return ;
	}
}
