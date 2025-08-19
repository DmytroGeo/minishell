/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:12:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/14 21:07:13 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "signals.h"

/**
 * @brief This function is the process loop, run if we have multiple processes
 * (and therefore need multiple children to execute them).
 * First, we call fork() and save its return to the int array pid. 
 * By calling fork(), we split the process into a parent and child process,
 * and the child process executes everything in the '(cshell->pid)[i] == 0'
 * loop. We have to be able to handle signals in child processes so
 * we use ????. do_redirections() does the relevant infile and outfile
 * redirections for that (ith) child process using the dup2 command.
 * close_pipes() closes all the read and write ends of the pipes so our 
 * minishell doesn't have any open fds at exit and execute_in_child runs
 * the relevant command (of the ith process)
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	process_loop(t_cshell *cshell)
{
	int		i;
	int		num_of_proc;

	i = 0;
	num_of_proc = cshell->num_of_proc;
	while (i < num_of_proc)
	{
		(cshell->pid)[i] = fork();
		if ((cshell->pid)[i] < 0)
			(free_whole_cshell(cshell), exit(EXIT_FAILURE));
		if ((cshell->pid)[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			do_redirections(i, cshell);
			close_pipes(cshell->fd, num_of_proc - 1);
			execute_in_child(i, cshell);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
