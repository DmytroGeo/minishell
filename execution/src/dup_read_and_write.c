/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_read_and_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:42:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/01 20:42:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	dup_infile(int **fd, int *pid, t_list **head, t_simple_command *simple_command)
{
	int		flag1;
	int		number_of_commands;
	char *infile = simple_command->infile;

	number_of_commands = ((t_execution_content *)((*head)->content))->number_of_commands;
	if (infile)
	{
		if (access(infile, F_OK) == 0)
		proc_call(access(infile, R_OK), 'a');
		flag1 = open(infile, O_RDONLY);
		if (flag1 < 0)
		{
			ft_perror(infile, 'o');
			close_fds(fd, number_of_commands - 1);
			free_and_exit(pid, fd, head);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(flag1, STDIN_FILENO), 'i');
		close(flag1);
	}
	return ;
}

void	dup_outfile(int **fd, int *pid, t_list **head, t_simple_command *simple_command)
{
	int		flag2;
	int		number_of_commands;
	char *outfile = simple_command->outfile;
	number_of_commands = ((t_execution_content *)((*head)->content))->number_of_commands;
	if (outfile)
	{
		if (*(simple_command->is_append) == 1)
			flag2 = open(outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else	
			flag2 = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (flag2 < 0)
		{
			perror(NULL);
			close_fds(fd, number_of_commands - 1);
			free_and_exit(pid, fd, head);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(flag2, STDOUT_FILENO), 'o');
		close(flag2);
	}
	return ;
}
