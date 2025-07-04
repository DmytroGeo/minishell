/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:12:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 10:26:57 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	process_loop(int *pid, int **fd, t_simple_command *simple_command, char **envp)
{
	int		i;
	int		number_of_commands;

	i = 0;
	number_of_commands = ft_array_len(simple_command->commands);
	while (i < number_of_commands)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			free_and_exit(pid, fd);
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0)
		{
			if (i == 0)
				dup_infile(fd, pid, simple_command);
			else
				proc_call(dup2(fd[i - 1][0], STDIN_FILENO), 'i');
			if (i == number_of_commands - 1)
				dup_outfile(fd, pid, simple_command);
			else
				proc_call(dup2(fd[i][1], STDOUT_FILENO), 'o');
			close_fds(fd, number_of_commands - 1);
			execute(i, fd, pid, simple_command, envp);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

