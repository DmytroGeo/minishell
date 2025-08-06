/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:12:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/06 17:23:37 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "signals.h"

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
			signal(SIGINT, handle_child_sigint);
			signal(SIGQUIT, handle_child_sigquit);
			dup_infile(i, cshell);
			dup_outfile(i, cshell);
			close_fds(cshell->fd, num_of_proc - 1);
			execute_in_child(i, cshell);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
