/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_infiles_and_outfiles.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:42:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 16:12:10 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	dup_infile(int i, int **fd, int *pid, t_main *main)
{
	int		num_inf;
	int		*infiles;
	int		counter;

	counter = 0;
	infiles = ((main->proc_array)[i]).infiles;
	num_inf = ((main->proc_array)[i]).num_inf;
	if (i != 0 && num_inf == 0)
	{
		proc_call(dup2(fd[i - 1][0], STDIN_FILENO), 'i');
		return ;
	}
	while (counter < num_inf)
	{
		if (infiles[counter] < 0)
		{
			close_fds(fd, main->num_of_proc - 1);
			free_and_exit(pid, fd, main);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(infiles[counter], STDIN_FILENO), 'i');
		close(infiles[counter]);
		counter++;
	}
	return ;
}


void	dup_outfile(int i, int **fd, int *pid, t_main *main)
{
	int		num_outf;
	int		*outfiles;
	int		counter;

	counter = 0;
	outfiles = ((main->proc_array)[i]).outfiles;
	num_outf = ((main->proc_array)[i]).num_outf;
	if (i != main->num_of_proc - 1 && num_outf == 0)
	{
		proc_call(dup2(fd[i][1], STDOUT_FILENO), 'o');
		return ;		
	}
	while (counter < num_outf)
	{
		if (outfiles[counter] < 0)
		{
			close_fds(fd, main->num_of_proc - 1);
			free_and_exit(pid, fd, main);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(outfiles[counter], STDOUT_FILENO), 'o');
		close(outfiles[counter]);
		counter++;
	}
	return ;
}
