/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/12 13:12:47 by dgeorgiy         ###   ########.fr       */
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
				return(outfile_err(file_name), number_of_outfiles + 1);
			number_of_outfiles++;			
		}
		start = start->next;
	}
	return (number_of_outfiles);
}

// In case we find no outfiles, this function redirects output to STD_OUT.

int	no_outfiles(t_proc *proc_struct)
{
	proc_struct->outfiles = malloc(2 * sizeof(int *));
	if (!(proc_struct->outfiles))
		return (-1);
	*((proc_struct->outfiles)[0]) = STDOUT_FILENO;
	((proc_struct->outfiles)[1]) = NULL;
	return (0);
}

// if we find an outfile, this function stores its fd in int **outfiles.
// In a list of N infiles where the Kth one is bad, we run this function K times,
// so when we run open on an outfile we don't have access to, we'll get our last outfile fd as -1.
// There is a check in dup write side (in execution) for any negative fds, which will exit the child 
// process before it executes

int init_outfile(int i, t_token *start, t_proc *proc_struct)
{
	char *file_name;
	int fd;

	file_name = ((t_token_content *)(start->content))->value;
	(proc_struct->outfiles)[i] = malloc(sizeof(int *));
	if (!((proc_struct->outfiles)[i]))
		return (-1);
	if (is_redir_out(start->previous))
	{
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		*((proc_struct->outfiles)[i]) = fd;	
	}
	else if (is_append(start->previous))
	{
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		*((proc_struct->outfiles)[i]) = fd;
	}
	return (0);
}

int    find_outfiles(t_proc *proc_struct, t_token *start)
{
	int number_of_outfiles;
	int i;
	
	i = 0;
	number_of_outfiles = find_number_of_outfiles(start);
	if (number_of_outfiles == 0)
		return (no_outfiles(proc_struct));
	proc_struct->outfiles = malloc((number_of_outfiles + 1) * sizeof(int *));
	if (!(proc_struct->outfiles))
		return (-1);
	while (i < number_of_outfiles) 
	{
		if ((is_redir_out(start) || is_append(start)))
		{
			start = start->next;
			if (init_outfile(i, start, proc_struct) < 0)
				return (free_outfiles(i, proc_struct), -1);
			i++;
		}
		start = start->next;
	}
	(proc_struct->outfiles)[number_of_outfiles] = NULL;
	return (0);   
}