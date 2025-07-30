/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/30 12:58:27 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	execute_in_child(int i, t_cshell *cshell)
{
	char	**args;
	t_proc	proc;

	proc = (cshell->proc_array)[i];
	if (is_builtin(proc.cmd_and_args[0]))
	{
		execute_built_ins(cshell, i, STDOUT_FILENO);
		(free_whole_cshell(cshell), exit(cshell->exit_code));
	}
	else
	{
		if (access((proc.cmd_and_args)[0], F_OK | X_OK) != 0)
			(free_whole_cshell(cshell), exit(127));
		else
		{
			args = (proc.cmd_and_args);
			if ((execve((proc.cmd_and_args)[0], args, cshell->envp)) < 0)
				(free_whole_cshell(cshell), exit(1));
		}
	}
}
