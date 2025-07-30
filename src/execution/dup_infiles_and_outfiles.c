/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_infiles_and_outfiles.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:42:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/29 12:23:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	dup_infile(int i, t_cshell *cshell)
{
	int		num_inf;
	int		*infiles;
	int		counter;

	counter = 0;
	infiles = ((cshell->proc_array)[i]).infiles;
	num_inf = ((cshell->proc_array)[i]).num_inf;
	if (i != 0 && num_inf == 0)
		return (proc_call(dup2((cshell->fd)[i - 1][0], STDIN_FILENO), 'i'));
	while (counter < num_inf)
	{
		if (infiles[counter] < 0)
		{
			close_fds(cshell->fd, cshell->num_of_proc - 1);
			free_whole_cshell(cshell);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(infiles[counter], STDIN_FILENO), 'i');
		close(infiles[counter]);
		counter++;
	}
	return ;
}

void	dup_outfile(int i, t_cshell *cshell)
{
	int		num_outf;
	int		*outfiles;
	int		counter;

	counter = 0;
	outfiles = ((cshell->proc_array)[i]).outfiles;
	num_outf = ((cshell->proc_array)[i]).num_outf;
	if (i != cshell->num_of_proc - 1 && num_outf == 0)
		return (proc_call(dup2((cshell->fd)[i][1], STDOUT_FILENO), 'o'));
	while (counter < num_outf)
	{
		if (outfiles[counter] < 0)
		{
			close_fds(cshell->fd, cshell->num_of_proc - 1);
			free_whole_cshell(cshell);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(outfiles[counter], STDOUT_FILENO), 'o');
		close(outfiles[counter]);
		counter++;
	}
	return ;
}
