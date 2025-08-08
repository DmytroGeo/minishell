/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:42:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:23:09 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

/**
 * @brief This function does all infile redirections. 
 * In case of one of the 'middle' processes (not first or last),
 * it checks whether we have any infiles we need to redirect from.
 * If there aren't any, it redirects input from STDIN to the read end 
 * of the (i-1)th pipe.
 * In case of a non-middle process, or if we need to redirect from infile(s),
 * we do our redirections in a loop. If we encounter a bad infile (fd < 0),
 * we exit the program (and don't execute).
 * @param i The number of the process.
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	redirect_in(int i, t_cshell *cshell)
{
	int		num_inf;
	int		*infiles;
	int		counter;

	counter = 0;
	infiles = ((cshell->proc_array)[i]).infiles;
	num_inf = ((cshell->proc_array)[i]).num_inf;
	if (i != 0 && num_inf == 0)
	{
		if (dup2((cshell->fd)[i - 1][0], STDIN_FILENO) < 0)
			return (perror(NULL));
	}
	while (counter < num_inf)
	{
		if (infiles[counter] < 0)
		{
			close_pipes(cshell->fd, cshell->num_of_proc - 1);
			exit_with_code(cshell, 1);
		}
		if (dup2(infiles[counter], STDIN_FILENO) < 0)
			perror(NULL);
		close(infiles[counter]);
		counter++;
	}
	return ;
}

/**
 * @brief This function does all outfile redirections. 
 * In case of one of the 'middle' processes (not first or last),
 * it checks whether we have any outfiles we need to redirect to.
 * If there aren't any, it redirects output from STDOUT to the write end 
 * of the (i)th pipe.
 * In case of a non-middle process, or if we need to redirect to outfile(s),
 * we do our redirections in a loop. If we encounter a bad outfile (fd < 0),
 * we exit the program (and don't execute).
 * @param i The number of the process.
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	redirect_out(int i, t_cshell *cshell)
{
	int		num_outf;
	int		*outfiles;
	int		counter;

	counter = 0;
	outfiles = ((cshell->proc_array)[i]).outfiles;
	num_outf = ((cshell->proc_array)[i]).num_outf;
	if (i != cshell->num_of_proc - 1 && num_outf == 0)
	{
		if (dup2((cshell->fd)[i][1], STDOUT_FILENO) < 0)
			return (perror(NULL));
	}
	while (counter < num_outf)
	{
		if (outfiles[counter] < 0)
		{
			close_pipes(cshell->fd, cshell->num_of_proc - 1);
			exit_with_code(cshell, 1);
		}
		if (dup2(outfiles[counter], STDOUT_FILENO) < 0)
			perror(NULL);
		close(outfiles[counter]);
		counter++;
	}
	return ;
}

void	do_redirections(int i, t_cshell *cshell)
{
	redirect_in(i, cshell);
	redirect_out(i, cshell);
}
