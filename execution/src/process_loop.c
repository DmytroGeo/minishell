/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:12:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/01 19:05:09 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	process_loop(t_list **head, int *pid, int **fd, t_simple_command *simple_command)
{
	int		i;
	int		number_of_commands;

	i = 0;
	number_of_commands = ((t_execution_content *)((*head)->content))->number_of_commands;
	while (i < number_of_commands)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			free_and_exit(pid, fd, head);
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
		{
			if (i == 0)
				dup_infile(fd, pid, head, simple_command);
			else
				proc_call(dup2(fd[i - 1][0], STDIN_FILENO), 'i');
			if (i == number_of_commands - 1)
				dup_outfile(fd, pid, head, simple_command);
			else
				proc_call(dup2(fd[i][1], STDOUT_FILENO), 'o');
			close_fds(fd, number_of_commands - 1);
			execute(i, fd, pid, head);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
