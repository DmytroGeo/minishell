/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/10 15:31:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

int	execution(t_big_struct *big_struct)
{
	int		exit_status;
	int		*pid;
	int		**fd;
	
	pid = NULL;
	fd = NULL;
	exit_status = 0;
	if (big_struct->num_of_proc == 1)
	{
		if (is_built_in(((big_struct->proc_array)[0]).command_and_args[0]))          
		{
			exit_status = execute_built_ins(big_struct, 0, pid, fd);
			free_big_struct(big_struct);
			return(exit_status);
		}
	}
	init_setup(&pid, &fd, big_struct);
	process_loop(pid, fd, big_struct);
	close_fds(fd, ft_array_len(simple_command->commands) - 1);
	ft_intarr_free(fd, ft_array_len(simple_command->commands) - 1);
	exit_status = wait_for_processes(pid, ft_array_len(simple_command->commands));
	free(pid);
	free_simple_command(simple_command);
	return (exit_status);
}