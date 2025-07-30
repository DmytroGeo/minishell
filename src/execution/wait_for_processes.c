/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:22:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/30 13:08:06 by dgeorgiy         ###   ########.fr       */
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
	if (WIFEXITED(status))
	{
		cshell->exit_code = WEXITSTATUS(status);
		return ;
	}
	cshell->exit_code = status;
	return ;
}
