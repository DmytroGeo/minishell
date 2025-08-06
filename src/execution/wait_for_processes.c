/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:22:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/06 12:55:27 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	wait_for_processes(t_cshell *cshell)
{
	int	k;
	int	status;
	int	wpid;

	k = 0;
	while (k < cshell->num_of_proc)
	{
		wpid = waitpid((cshell->pid)[k], &status, 0);
		if (wpid == -1)
			free(cshell->pid);
		k++;
	}
	if (WIFSIGNALED(status))
	{
		cshell->exec_code = WTERMSIG(status);
		if (cshell->exec_code == SIGQUIT)
			write(2, "Quit: 3\n", 8);
		else if(cshell->exec_code == SIGINT)
			write(1, "\n", 1);
		return ;
	}
	if (WIFEXITED(status))
	{
		cshell->exec_code = WEXITSTATUS(status);
		return ;
	}
	cshell->exec_code = status;
	return ;
}
