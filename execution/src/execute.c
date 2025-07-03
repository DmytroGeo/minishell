/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/02 17:32:41 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute(int i, int **fd, int *pid, t_list **head)
{
	char	**array;
	t_list	*node;
	int		n;
	t_execution_content *node_content;
	
	node = ft_find_node(i, head);
	node_content = node->content;
	array = malloc((2 + ft_array_len((node_content->flags))) * sizeof(char *));
	if (!array)
		return ;
	array[0] = node_content->path;
	if (!array[0] && !is_built_in(node_content->command_name))
	{
		ft_array_free(array, ft_array_len(array));
		free_and_exit(pid, fd, head);
		exit (127);
	}
	n = 0;
	while (++n <= ft_array_len(node_content->flags))
		array[n] = (node_content->flags)[n - 1];
	array[n] = NULL;
	if (is_built_in(node_content->command_name))
	{
		execute_built_ins_in_child(node_content->command_name, array, *head);
		ft_array_free(array, ft_array_len(array));
		free_and_exit(pid, fd, head);
		exit(errno);
	}
	else
	{
		if (execve(node_content->path, array, (((t_execution_content *)((*head)->content))->envp)) < 0)
		{
			ft_array_free(array, ft_array_len(array));
			free_and_exit(pid, fd, head);
			return ;
		}	
	}
}
