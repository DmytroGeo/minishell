/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:31:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/14 08:20:54 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execution(int n, char **processed_command, char **envp)
{
	int		*pid;
	int		**fd;
	t_list	*head;
	int		exit_status;

	head = NULL;
	pid = NULL;
	fd = NULL;
	proc_call(n, 'r');
	init_list(n, processed_command, envp, &head);
	// free processed_command
	init_setup(&pid, &fd, n, &head);
	process_loop(&head, pid, fd);
	close_fds(fd, n - 4);
	ft_lstclear(&head);
	ft_intarr_free(fd, n - 4);
	exit_status = wait_for_processes(pid, n);
	free(pid);
	return (exit_status);
}
