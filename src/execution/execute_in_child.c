/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/06 12:52:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	exit_with_code(t_cshell *cshell, int i)
{
	cshell->exec_code = i;
	(free_whole_cshell(cshell), exit(cshell->exec_code));
}

void	execute_in_child(int i, t_cshell *cshell)
{
	t_proc	proc;

	proc = (cshell->proc_array)[i];
	if (is_builtin(proc.cmd_and_args[0]))
	{
		execute_built_ins(cshell, i, STDOUT_FILENO);
		exit_with_code(cshell, cshell->exec_code);
	}
	if (access((proc.cmd_and_args)[0], F_OK | X_OK) != 0)
		exit_with_code(cshell, 127);
	if ((execve((proc.cmd_and_args)[0], proc.cmd_and_args, cshell->envp)) < 0)
		exit_with_code(cshell, 1);
}
