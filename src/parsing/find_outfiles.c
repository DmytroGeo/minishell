/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 21:37:03 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

/**
 * @brief This function is analagous to find_number_of_infiles.
 * Important to note: Unlike infiles, if an outfile doesn't exist it is
 * created, so the only thing that can go wrong is if we are trying to write to 
 * an outfile that does exist but has the wrong permissions.
 * In the case of the process having at least one outfile that has the wrong 
 * permissions, as with infiles I count all legal outfiles + first illegal
 * outfile. This is so that when we run init_outfile,
 * open() gets run on the bad outfile which gives us an fd of -1. Therefore,
 * in src->execution->do_redirections.c, when we go through the fd array in a
 * loop, we'll eventually encounter the bad one and free everything and exit.
 * Very important to exit in execution and not in parsing.
 * @param start The start of our token chain
 * @return the number of outfiles.
 */
int	find_number_of_outfiles(t_token *start)
{
	int		number_of_outfiles;
	char	*file_name;

	number_of_outfiles = 0;
	while (start && !is_pipe(start))
	{
		if (is_redir_out(start) || is_append(start))
		{
			start = start->next;
			file_name = ((t_tok_cont *)(start->content))->value;
			if (access(file_name, F_OK) == 0 && access(file_name, W_OK) != 0)
				return (permission_error(file_name), number_of_outfiles + 1);
			number_of_outfiles++;
		}
		start = start->next;
	}
	return (number_of_outfiles);
}

int	init_outfile(int i, t_token *start, t_proc *proc)
{
	char	*file_name;
	int		fd;

	fd = 0;
	file_name = ((t_tok_cont *)(start->content))->value;
	if (is_redir_out(start->previous))
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (is_append(start->previous))
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	(proc->outfiles)[i] = fd;
	return (0);
}

/**
 * @brief This function initialises our array of outfiles for
 * the process at address proc. An outfile is defined as a file
 * that follows > or >>. Important to note:
 * in the case of multiple outfiles, only the last one is written into.
 * In the case of wrong permissions for (at least one of) the outfiles
 * in a process, the command of that process is not executed.
 * (see src->execution->do_redirections.c).
 * @param start The start of our token chain
 * @param proc The address of our current proc structure.
 * @return 0 on success, -42 on failed memory allocation.
 */
int	find_outfiles(t_proc *proc, t_token *start)
{
	int	i;

	i = 0;
	proc->num_outf = find_number_of_outfiles(start);
	if (proc->num_outf == 0)
		return (0);
	proc->outfiles = ft_calloc(proc->num_outf, sizeof(int));
	if (!(proc->outfiles))
		return (-42);
	while (i < proc->num_outf)
	{
		if ((is_redir_out(start) || is_append(start)))
		{
			start = start->next;
			init_outfile(i, start, proc);
			i++;
		}
		start = start->next;
	}
	return (0);
}
