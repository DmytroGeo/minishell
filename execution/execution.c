/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 13:29:54 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

void	evaluate_and_execute(t_cshell *cshell, int *exit_code)
{
	if (*exit_code == 0)
	{
		*exit_code = execution(cshell);
		return;	
	}
	else
		return (free_cshell(cshell));
}

int	execution(t_cshell *cshell)
{
	int		exit_code;
	char	*first_command;

	exit_code = 0;
	first_command = ((cshell->proc_array)[0]).cmd_and_args[0];
	if (cshell->num_of_proc == 1 && is_built_in(first_command))
		return (execute_in_main(cshell));
	init_setup(cshell);
	process_loop(cshell);
	close_fds(cshell->fd, cshell->num_of_proc - 1);
	exit_code = wait_for_processes(cshell->pid, cshell->num_of_proc);
	free_cshell(cshell);
	return (exit_code);
}