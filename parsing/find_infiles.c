/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:12:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/10 13:50:13 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_redir_in(t_token *current_token)
{
    return (current_token->type == redir_in);
}

int is_heredoc(t_token *current_token)
{
    return (current_token->type == heredoc);
}

// if even one of the infiles in the process doesn't exist or doesn't have read permissions, that process doesn't execute
// however, all the other processes do.

// int		find_infiles(t_proc_struct *process, t_token *start)
// {
// 	int		number_of_infiles;
// 	int		i;
// 	char	*limiter;
// 	int		*fd;

// 	i = 0;
// 	number_of_infiles = find_number_of_infiles(start);
// 	if (number_of_infiles < 0)
// 		return (-1);
// 	process->infiles = malloc((number_of_infiles + 1) * sizeof(int *));
// 	while (!is_eof(start) && !is_pipe(start))
// 	{
// 		if (is_redir_in(start))
// 		{
// 			start = start->next;
// 			(process->infiles)[i] = malloc(sizeof(int *));
// 			*((process->infiles)[i]) = open(start->value, O_RDONLY);
// 			i++;
// 		}
// 		else if (is_heredoc(start))
// 		{
// 			limiter = start->next->value;
// 			fd = malloc(2 * sizeof(int));
// 			pipe(fd);
// 			while (1)
// 			{
// 				write(1, "> ", 2);
// 				char *line_read = get_next_line(0);
// 				if (ft_strncmp(line_read, limiter, ft_strlen(limiter)) == 0 && ft_strncmp(line_read, limiter, ft_strlen(line_read) - 1) == 0)
// 				{
// 					*((process->infiles)[i]) = fd[0];
// 					close(fd[1]);               
// 					break;
// 				}
// 				else
// 					write(fd[1], line_read, ft_strlen(line_read));
// 			}
// 		}
// 		start = start->next;
// 	}
// 	(process->infiles)[number_of_infiles] = NULL;
// 	return (0);
// }

int		return_heredoc(char *limiter)
{
	int *fd;
	int read_end;
	
	read_end = -1;
	fd = malloc(2 * sizeof(int));
	if (!fd)
		return (read_end);
	pipe(fd);
	while (1)
	{
		write(1, "> ", 2);
		char *line_read = get_next_line(0);
		if (ft_strncmp(line_read, limiter, ft_strlen(limiter)) == 0 && ft_strncmp(line_read, limiter, ft_strlen(line_read) - 1) == 0)
		{
			read_end = fd[0];
			close(fd[1]);        
			break;
		}
		else
			write(fd[1], line_read, ft_strlen(line_read));
	}
	return (read_end);
}

int		find_infiles(t_proc_struct *process, t_token *start)
{
	int		number_of_infiles;
	int		i;

	i = 0;
	number_of_infiles = find_number_of_infiles(start);
	if (number_of_infiles < 0)
		return (-1);
	process->infiles = malloc((number_of_infiles + 1) * sizeof(int *));
	while (!is_eof(start) && !is_pipe(start))
	{
		if (is_redir_in(start) || is_heredoc(start))
		{
			start = start->next;
			(process->infiles)[i] = malloc(sizeof(int *));
			if (is_redir_in(start->previous))
				*((process->infiles)[i]) = open(start->value, O_RDONLY);
			else if (is_heredoc(start->previous))
				*((process->infiles)[i]) = return_heredoc(start->value);
			i++;
		}
		start = start->next;
	}
	(process->infiles)[number_of_infiles] = NULL;
	return (0);
}