/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 12:55:07 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute(int i, int **fd, int *pid, t_main *main)
{
	int exit_code;
	char **args;
	t_proc proc;
	
	exit_code = 0;
	proc = (main->proc_array)[i];
    if (is_built_in(proc.cmd_and_args[0]))
	{		
		exit_code = execute_built_ins(main, i, pid, fd);
		(free_and_exit(pid, fd, main), exit(exit_code));
	}
    else
    {
    	if (access((proc.cmd_and_args)[0], F_OK | X_OK) != 0)
			(free_and_exit(pid, fd, main), exit(127));
		else
		{
			args = (proc.cmd_and_args) + 1;
			if ((execve((proc.cmd_and_args)[0], args, main->envp)) < 0)
				(free_and_exit(pid, fd, main), exit(1));
		}
	}
}