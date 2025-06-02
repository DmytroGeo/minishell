/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:29:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/01 14:02:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_and_exit(int *pid, int **fd, t_list **head)
{
	int		number_of_commands;

	if (!fd)
		return ;
	number_of_commands = ((t_execution_content *)((*head)->content))->number_of_commands;
	free(pid);
	ft_intarr_free(fd, number_of_commands - 1);
	ft_lstclear(head, ft_free_paths_and_flags);
	return ;
}
