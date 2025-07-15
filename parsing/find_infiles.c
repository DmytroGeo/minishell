/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:12:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 14:33:09 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int find_number_of_infiles(t_token *start)
{
	int	number_of_infiles;
	char *file_name;
	
	number_of_infiles = 0;
	while (!is_eof(start) && !is_pipe(start))
	{
		if (is_heredoc(start) || is_redir_in(start))
		{
			start = start->next;
			file_name = ((t_token_content *)(start->content))->value;
			// if (is_heredoc(start->previous) && !is_valid_heredoc_name(file_name))
			// 	infile_err1(file_name);
			if (is_redir_in(start->previous) && access(file_name, F_OK) != 0)
				infile_err2(file_name);
			else if (is_redir_in(start->previous) && access(file_name, R_OK) != 0)
				infile_err3(file_name);
			number_of_infiles++;
		}
		start = start->next;
	}										
	return (number_of_infiles);
}

int init_infile(int i, t_token *start, t_proc *proc)
{
	char *file_name;

	file_name = ((t_token_content *)(start->content))->value;
	if (is_redir_in(start->previous))
		(proc->infiles)[i] = open(file_name, O_RDONLY);
	else if (is_heredoc(start->previous))
		(proc->infiles)[i] = heredoc_fd(file_name);
	return (0);
}

int		find_infiles(t_proc *proc, t_token *start)
{
	int		i;

	i = 0;
	proc->num_inf = find_number_of_infiles(start);
	if (proc->num_inf < 0)
		return (-1);
	proc->infiles = malloc((proc->num_inf) * sizeof(int));
	if (!(proc->infiles))
		return (-2);
	while (i < proc->num_inf)
	{
		if (is_redir_in(start) || is_heredoc(start))
		{
			start = start->next;
			init_infile(i, start, proc);
			i++;
		}
		start = start->next;
	}
	return (0);
}
