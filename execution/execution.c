/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/04 21:08:47 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

int	execution(int number_of_commands, t_simple_command *simple_command, char **envp)
{
	int		*pid;
	int		**fd;
	t_list	*head;
	int		exit_status;

	head = NULL;
	pid = NULL;
	fd = NULL;
	init_list(number_of_commands, simple_command->commands, envp, &head); // this should be ok
	init_setup(&pid, &fd, number_of_commands, &head); // this should also be ok
	process_loop(&head, pid, fd, simple_command);
	close_fds(fd, number_of_commands - 1);
	ft_lstclear(&head, ft_free_paths_and_flags);
	ft_intarr_free(fd, number_of_commands - 1);
	exit_status = wait_for_processes(pid, number_of_commands);
	free(pid); 
	return (exit_status); 
	
}
 