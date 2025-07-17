/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 18:01:46 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

int	evaluate_and_execute(t_main *main, int exit_code)
{
	if (exit_code == 0)
		return (execution(main));
	else
		return (exit_code);
}

int	execution(t_main *main)
{
	int		exit_code;
	int		*pid;
	int		**fd;
	char	*first_command;
	
	pid = NULL;
	fd = NULL;
	exit_code = 0;
	first_command = ((main->proc_array)[0]).cmd_and_args[0];
	if (main->num_of_proc == 1 && is_built_in(first_command))
		return (execute_in_main(main, pid, fd));
	init_setup(&pid, &fd, main);
	process_loop(pid, fd, main);
	close_fds(fd, main->num_of_proc - 1);
	ft_array_free2((void **)fd, main->num_of_proc - 1);
	exit_code = wait_for_processes(pid, main->num_of_proc);
	free(pid);
	free_main(main);
	return (exit_code);
}