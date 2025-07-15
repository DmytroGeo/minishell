/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 16:12:53 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

int	execution(t_main *main)
{
	int		exit_status;
	int		*pid;
	int		**fd;
	char	*first_command;
	
	pid = NULL;
	fd = NULL;
	exit_status = 0;
	first_command = ((main->proc_array)[0]).cmd_and_args[0];
	if (main->num_of_proc == 1 && is_built_in(first_command))
		return (execute_in_main(main, pid, fd));
	init_setup(&pid, &fd, main);
	process_loop(pid, fd, main);
	close_fds(fd, main->num_of_proc - 1);
	ft_array_free((void **)fd, main->num_of_proc - 1);
	exit_status = wait_for_processes(pid, main->num_of_proc);
	free(pid);
	free_main(main);
	return (exit_status);
}