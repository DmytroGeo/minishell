/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:12:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/12 10:27:11 by dgeorgiy         ###   ########.fr       */
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
			if (is_heredoc(start->previous) && !is_valid_heredoc_name(file_name))
				return (infile_err1(file_name), -1);
			else if (is_redir_in(start->previous) && access(file_name, F_OK) != 0)
				return (infile_err2(file_name), -1);
			else if (is_redir_in(start->previous) && access(file_name, R_OK) != 0)
				return (ifile_err3(file_name), -1);
			number_of_infiles++;
		}
		start = start->next;
	}										
	return (number_of_infiles);
}

int		no_infiles(t_proc *proc_struct)
{
	proc_struct->infiles = malloc(2 * sizeof(int *));
	if (!(proc_struct->infiles))
		return (-2);
	*((proc_struct->infiles)[0]) = STDIN_FILENO;
	((proc_struct->infiles)[1]) = NULL;
	return (0);
}

int init_infile(int i, t_token *start, t_proc *proc_struct)
{
	char *file_name;

	file_name = ((t_token_content *)(start->content))->value;
	(proc_struct->infiles)[i] = malloc(sizeof(int *));
	if (!((proc_struct->infiles)[i]))
		return (-2);
	if (is_redir_in(start->previous))
		*((proc_struct->infiles)[i]) = open(file_name, O_RDONLY);
	else if (is_heredoc(start->previous))
		*((proc_struct->infiles)[i]) = heredoc_fd(file_name);
	return (0);
}

int		find_infiles(t_proc *proc_struct, t_token *start)
{
	int		number_of_infiles;
	int		i;

	i = 0;
	number_of_infiles = find_number_of_infiles(start);
	if (number_of_infiles < 0)
		return (-1);
	else if (number_of_infiles == 0)
		return(no_infiles(proc_struct));
	proc_struct->infiles = malloc((number_of_infiles + 1) * sizeof(int *));
	if (!(proc_struct->infiles))
		return (-2);
	while (i < number_of_infiles)
	{
		if (is_redir_in(start) || is_heredoc(start))
		{
			start = start->next;
			if (init_infile(i, start, proc_struct) == -2)
				return (free_infiles(i, proc_struct), -2); 
			i++;
		}
		start = start->next;
	}
	(proc_struct->infiles)[number_of_infiles] = NULL;
	return (0);
}
