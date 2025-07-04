/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_read_and_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:42:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 13:08:34 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	dup_infile(int **fd, int *pid, t_simple_command *simple_command)
{
	int		number_of_commands;
	int		number_of_infiles;
	int		**infiles;
	int		i = 0;

	infiles = simple_command->infiles;
	number_of_commands = ft_array_len(simple_command->commands);
	number_of_infiles = ft_int_array_len(simple_command->infiles);
	while (i < number_of_infiles)
	{
		if (*(infiles[i]) < 0)
		{
			perror(NULL);
			close_fds(fd, number_of_commands - 1);
			free_and_exit(pid, fd, simple_command);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(*(infiles[i]), STDIN_FILENO), 'i');
		close(*(infiles[i]));
		i++;
	}
	return ;
}

void	dup_outfile(int **fd, int *pid, t_simple_command *simple_command)
{
	int		number_of_commands;
	int		number_of_outfiles;
	int		**outfile;
	int		i = 0;

	outfile = simple_command->outfiles;
	number_of_commands = ft_array_len(simple_command->commands);
	number_of_outfiles = ft_int_array_len(simple_command->outfiles);
	while (i < number_of_outfiles)
	{
		if (*(outfile[i]) < 0)
		{
			perror("No access");
			close_fds(fd, number_of_commands - 1);
			free_and_exit(pid, fd, simple_command);
			exit(EXIT_FAILURE);
		}
		proc_call(dup2(*(outfile[i]), STDOUT_FILENO), 'o');
		close(*(outfile[i]));
		i++;
	}
	return ;
}
