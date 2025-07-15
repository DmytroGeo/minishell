/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:12:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 12:58:34 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	process_loop(int *pid, int **fd, t_main *main)
{
	int		i;
	int		num_of_proc;

	i = 0;
	num_of_proc = main->num_of_proc;
	while (i < num_of_proc)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			(free_and_exit(pid, fd, main), exit(EXIT_FAILURE));
		if (pid[i] == 0)
		{
			dup_infile(i, fd, pid, main);
			dup_outfile(i, fd, pid, main);
			close_fds(fd, num_of_proc - 1);
			execute(i, fd, pid, main);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
