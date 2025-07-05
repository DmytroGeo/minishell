/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:30:07 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute(char *command_to_be_executed, int **fd, int *pid, t_simple_command *simple_command)
{
	char **array = ft_split(command_to_be_executed, ' ');
	char *path;
	int exit_code = 0;
		
    if (is_built_in(array[0]))
	{		
		exit_code = execute_built_ins(simple_command, command_to_be_executed, pid, fd);
		(ft_array_free(array, ft_array_len(array)), free_and_exit(pid, fd, simple_command));
		exit(exit_code);	
	}
    else
    {
        path = get_path(array[0], *(simple_command->address_of_envp));
    	if (!path)
		{
			ft_perror(array[0], 'p');
			(ft_array_free(array, ft_array_len(array)), free_and_exit(pid, fd, simple_command));
			exit (127);			
		}
		else
		{
			if ((execve(path, array + 1, *(simple_command->address_of_envp))) < 0)
			{
				(free(path), ft_array_free(array, ft_array_len(array)), free_and_exit(pid, fd, simple_command));
				exit(-1) ;
			}
		}
	}
}