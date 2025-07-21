/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 17:01:48 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute(int i, t_cshell *cshell)
{
	int		exit_code;
	char	**args;
	t_proc	proc;

	exit_code = 0;
	proc = (cshell->proc_array)[i];
	if (is_builtin(proc.cmd_and_args[0]))
	{
		exit_code = execute_built_ins(cshell, i, STDOUT_FILENO);
		(free_cshell(cshell), exit(exit_code));
	}
	else
	{
		if (access((proc.cmd_and_args)[0], F_OK | X_OK) != 0)
			(free_cshell(cshell), exit(127));
		else
		{			
			args = (proc.cmd_and_args);
			if ((execve((proc.cmd_and_args)[0], args, cshell->envp)) < 0)
				(free_cshell(cshell), exit(1));
		}
	}
}
