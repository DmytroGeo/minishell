/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 13:11:36 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute(int i, int **fd, int *pid, char **envp, t_simple_command *simple_command)
{
	char *command_to_be_executed = (simple_command->commands)[i];
	char *array = ft_split(command_to_be_executed, ' ');
	char *path;
	
    if (is_built_in(array[0]))
	{
		execute_built_ins(simple_command, envp, prompt, (simple_command->commands)[i]); /////// I think we need to stitch more things into t_simple_command; envp, prompt, exit_status.
		ft_array_free(array, ft_array_len(array));
		free_and_exit(pid, fd, simple_command);
		exit(errno);		
	}
    else
    {
        path = get_path(array[0], envp);
    	if (!path)
		{
			ft_perror(array[0], 'p');
			// free path
			ft_array_free(array, ft_array_len(array));
			free_and_exit(pid, fd, simple_command);
			exit (127);			
		}
		else
		{
			if ((execve(path, array + 1, envp)) < 0)
			{
				ft_array_free(array, ft_array_len(array));
				free_and_exit(pid, fd, simple_command);
				return ;
			}
		}
	}
}