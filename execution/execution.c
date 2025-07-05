/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 13:09:57 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

int	execution(t_simple_command *simple_command)
{
	int		exit_status;
	int		*pid;
	int		**fd;
	
	pid = NULL;
	fd = NULL;
	if (ft_array_len(simple_command->commands) == 1 && is_built_in((simple_command->commands)[1]) == 1)
	{	
		exit_status = execute_built_ins(simple_command, (simple_command->commands)[1], pid, fd);
		free_simple_command(simple_command);
		return(exit_status);
	}
	init_setup(&pid, &fd, simple_command);
	process_loop(pid, fd, simple_command);
	close_fds(fd, ft_array_len(simple_command->commands) - 1);
	free_simple_command(simple_command);
	ft_intarr_free(fd, ft_array_len(simple_command->commands) - 1);
	exit_status = wait_for_processes(pid, ft_array_len(simple_command->commands));
	free(pid);
	return (exit_status);
}