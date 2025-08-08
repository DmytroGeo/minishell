/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:12:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 21:37:25 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

/**
 * @brief This function counts the number of infiles in a
 * process. Important to note: In the case of the process having at least one
 * infile that doesn't exist or has the wrong permissions, I count all the
 * legal infiles + first illegal infile. This is so that when we run init_infile,
 * open() gets run on the bad infile which gives us an fd of -1. Therefore,
 * in src->execution->do_redirections.c, when we go through the fd array in a
 * loop, we'll eventually encounter the bad one and free everything and exit.
 * Very important to exit in execution and not in parsing.
 * @param start The start of our token chain
 * @return the number of infiles.
 */
int	find_number_of_infiles(t_token *start)
{
	int		number_of_infiles;
	char	*file_name;

	number_of_infiles = 0;
	while (start && !is_pipe(start))
	{
		if (is_heredoc(start) || is_redir_in(start))
		{
			start = start->next;
			file_name = ((t_tok_cont *)(start->content))->value;
			if (is_redir_in(start->previous) && access(file_name, F_OK))
				return (existence_error(file_name), number_of_infiles + 1);
			else if (is_redir_in(start->previous) && access(file_name, R_OK))
				return (permission_error(file_name), number_of_infiles + 1);
			number_of_infiles++;
		}
		start = start->next;
	}
	return (number_of_infiles);
}

int	init_infile(int i, t_token *start, t_proc *proc)
{
	char	*file_name;
	int		fd;

	file_name = ((t_tok_cont *)(start->content))->value;
	if (is_redir_in(start->previous))
	{
		fd = open(file_name, O_RDONLY);
		(proc->infiles)[i] = fd;
	}
	else if (is_heredoc(start->previous))
	{
		fd = heredoc_fd(file_name);
		if (fd == -42)
			return (-42);
		else
			(proc->infiles)[i] = fd;
	}
	return (0);
}

/**
 * @brief This function initialises our array of infiles for
 * the process at address proc. An infile is defined as a file
 * that follows < or a heredoc. Important to note:
 * in the case of multiple infiles, only the last one is read from.
 * In the case of wrong permissions for (at least one of) the infiles
 * in a process, the command of that process is not executed.
 * (see src->execution->do_redirections.c).
 * @param start The start of our token chain
 * @param proc The address of our current proc structure.
 * @return 0 on success, -42 on failed memory allocation.
 */
int	find_infiles(t_proc *proc, t_token *start)
{
	int	i;

	i = 0;
	proc->num_inf = find_number_of_infiles(start);
	if (proc->num_inf == 0)
		return (0);
	proc->infiles = ft_calloc((proc->num_inf), sizeof(int));
	if (!(proc->infiles))
		return (-42);
	while (i < proc->num_inf)
	{
		if (is_redir_in(start) || is_heredoc(start))
		{
			start = start->next;
			if (init_infile(i, start, proc) == -42)
				return (-42);
			i++;
		}
		start = start->next;
	}
	return (0);
}
