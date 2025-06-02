/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/31 17:06:09 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute(int i, int **fd, int *pid, t_list **head)
{
	char	**array;
	t_list	*node;
	int		n;

	node = ft_find_node(i, head);
	array = malloc((2 + ft_array_len(((t_execution_content *)(node->content))->flags)) * sizeof(char *));
	if (!array)
		return ;
	array[0] = ((t_execution_content *)(node->content))->path;
	if (!array[0])
	{
		ft_array_free(array, ft_array_len(array));
		free_and_exit(pid, fd, head);
		exit (127);
	}
	n = 0;
	while (++n <= ft_array_len(((t_execution_content *)(node->content))->flags))
		array[n] = (((t_execution_content *)(node->content))->flags)[n - 1];
	array[n] = NULL;
	if (execve(((t_execution_content *)(node->content))->path, array, ((t_execution_content *)((*head)->content))->envp) < 0)
	{
		ft_array_free(array, ft_array_len(array));
		free_and_exit(pid, fd, head);
		return ;
	}
}
