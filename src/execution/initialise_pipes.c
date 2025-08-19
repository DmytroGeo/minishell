/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:17:14 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

/**
 * @brief This function initialises the integer array pid
 * and the array of pipes fd.
 * The purpose of the pid array is to store the exit status of each process
 * we run, so that we can save the exit code of the last process in
 * wait_for_processes(). The purpose of the 2d fd array is that when we run
 * pipe() on each of the fd[2] arrays, we'll be able to use fd[n][0] as the
 * read end of the nth pipe and fd[n][1] as the write end of the nth pipe.
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	initialise_pipes(t_cshell *cshell)
{
	int	i;

	i = -1;
	cshell->pid = ft_calloc(cshell->num_of_proc, sizeof(int));
	if (!cshell->pid)
		return (free_whole_cshell(cshell), exit(1));
	cshell->fd = ft_calloc(cshell->num_of_proc - 1, sizeof(int *));
	if (!cshell->fd)
		return (free_whole_cshell(cshell), exit(1));
	while (++i < cshell->num_of_proc - 1)
	{
		(cshell->fd)[i] = ft_calloc(2, sizeof(int));
		if (!(cshell->fd)[i])
			(free_whole_cshell(cshell), exit(1));
		if (pipe((cshell->fd)[i]) < 0)
		{
			(perror(NULL), close_pipes(cshell->fd, i + 1));
			(free_whole_cshell(cshell), exit(1));
		}
	}
}
