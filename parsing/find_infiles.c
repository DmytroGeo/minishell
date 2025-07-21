/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:12:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 16:10:00 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			file_name = ((t_token_content *)(start->content))->value;
			if (is_redir_in(start->previous) && access(file_name, F_OK))
				infile_err2(file_name);
			else if (is_redir_in(start->previous) && access(file_name, R_OK))
				infile_err3(file_name);
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

	file_name = ((t_token_content *)(start->content))->value;
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
