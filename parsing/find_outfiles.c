/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 12:12:05 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// this function finds the number of outfiles in the current process (up to and including the bad one).
// if an outfile exists and we don't have permission to access it, the function stops there.
// EXAMPLE: if we had echo hello > out1 > out2 > out3 and we didn't have permissions to access out2,
// only out1 will be made. The function won't be executed (see init outfile).

int find_number_of_outfiles(t_token *start)
{
	int number_of_outfiles;
	char *file_name;
	
	number_of_outfiles = 0;
	while (!is_eof(start) && !is_pipe(start))
	{
		if (is_redir_out(start) || is_append(start))
		{
			start = start->next;
			file_name = ((t_token_content *)(start->content))->value;
			if (access(file_name, F_OK) == 0 && access(file_name, W_OK) != 0)
				return (outfile_err(file_name), number_of_outfiles + 1);
			number_of_outfiles++;			
		}
		start = start->next;
	}
	return (number_of_outfiles);
}

int init_outfile(int i, t_token *start, t_proc *proc_struct)
{
	char *file_name;
	int fd;

	fd = 0;
	file_name = ((t_token_content *)(start->content))->value;
	if (is_redir_out(start->previous))
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (is_append(start->previous))
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	(proc_struct->outfiles)[i] = fd;
	return (0);
}

int    find_outfiles(t_proc *proc, t_token *start)
{
	int i;
	
	i = 0;
	proc->num_outf = find_number_of_outfiles(start);
	if (proc->num_outf == 0)
		return (0);
	proc->outfiles = malloc(proc->num_outf * sizeof(int));
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