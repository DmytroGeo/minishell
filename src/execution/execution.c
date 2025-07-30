/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/30 13:08:51 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	evaluate_and_execute(t_cshell *cshell)
{
	if (cshell->exit_code == 0)
	{
		execution(cshell);
		return ;
	}
	return (free_cshell(cshell));
}

void	execution(t_cshell *cshell)
{
	char	*first_command;

	first_command = ((cshell->proc_array)[0]).cmd_and_args[0];
	if (cshell->num_of_proc == 1 && is_builtin(first_command))
	{
		execute_in_main(cshell);
		return ;		
	}
	init_setup(cshell);
	process_loop(cshell);
	close_fds(cshell->fd, cshell->num_of_proc - 1);
	wait_for_processes(cshell);
	free_cshell(cshell);
}
