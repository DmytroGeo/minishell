/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:22:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:39:16 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	signal_status(t_cshell *cshell, int status)
{
	cshell->exit_code = WTERMSIG(status);
	if (cshell->exit_code == SIGQUIT)
		write(2, "Quit: 3\n", 8);
	else if (cshell->exit_code == SIGINT)
		write(1, "\n", 1);
	return ;
}

/**
 * @brief In this function, we use waitpid() to wait for the exit status of the 
 * ith command, which we save in the int status. We do this in a loop, because
 * we only care about the exit status of the last process.
 * If we exited because of a signal, we save that code to the cshell attribute
 * exit_code. Otherwise, if we exit the child process normally,
 * we save that code to the cshell attribute exit_code.
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	wait_for_processes(t_cshell *cshell)
{
	int	i;
	int	status;
	int	wpid;

	i = 0;
	while (i < cshell->num_of_proc)
	{
		wpid = waitpid((cshell->pid)[i], &status, 0);
		if (wpid == -1)
			(free_whole_cshell(cshell), exit(1));
		i++;
	}
	if (WIFSIGNALED(status))
		return (signal_status(cshell, status));
	if (WIFEXITED(status))
	{
		cshell->exit_code = WEXITSTATUS(status);
		return ;
	}
	cshell->exit_code = status;
	return ;
}
