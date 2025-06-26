/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_read_and_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:42:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/25 21:32:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	dup_infile(int **fd, int *pid, t_list **head, t_simple_command *simple_command)
{
	int		number_of_commands;
	int		*infile;
	
	infile = simple_command->infile;
	number_of_commands = ((t_execution_content *)((*head)->content))->number_of_commands;
	if (infile)
	{
		if (*infile < 0)
		{
			perror(NULL);
			close_fds(fd, number_of_commands - 1);
			free_and_exit(pid, fd, head);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(*infile, STDIN_FILENO), 'i');
		close(*infile);
	}
	return ;
}

void	dup_outfile(int **fd, int *pid, t_list **head, t_simple_command *simple_command)
{
	int		number_of_commands;
	int		number_of_outfiles;
	int		**outfile;
	int		i = 0;

	outfile = simple_command->outfile;
	number_of_commands = ft_array_len(simple_command->commands);
	number_of_outfiles = ft_int_array_len(simple_command->outfile);
	while (i < number_of_outfiles)
	{
		if (*(outfile[i]) < 0)
		{
			perror("No access");
			close_fds(fd, number_of_commands - 1);
			free_and_exit(pid, fd, head);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(*(outfile[i]), STDOUT_FILENO), 'o');
		close(*(outfile[i]));
		i++;
	}
	return ;
}
