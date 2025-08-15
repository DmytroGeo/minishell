/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/15 11:26:21 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

/**
 * @brief This function executes commands in the child process.
 * It's called on every process unless 1) we only have one process
 * AND 2) that process is a built in. So built ins are executed 
 * in child processes if those processes aren't the first one,
 * and every other command that's not a built-in (cat, ls, clear, wc, etc.)
 * is executed in a child process,
 * regardless of whether it's the first process or not.
 * The first thing we check is if the command is a built-in or not.
 * The second thing we check is if the command is in PATH (remember, in parsing,
 * we converted every function which we could find in PATH to it's full path,
 * so cat would become /usr/bin/cat in parsing).
 * Access returns 0 if the command is in path. Then we run execve, which takes 
 * the full path of our command, all its arguments and ENVP. 
 * In case of error, we free and exit, setting the relevant exit code.
 * @param i The number of the process.
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	execute_in_child(int i, t_cshell *cshell)
{
	t_proc	proc;

	proc = (cshell->proc_array)[i];
	if (is_builtin(proc.cmd_and_args[0]))
	{
		execute_built_ins(cshell, i, STDOUT_FILENO);
		exit_with_code(cshell, cshell->exit_code);
	}
	if (!ft_strchr((proc.cmd_and_args)[0], '/'))
		exit_with_code(cshell, 127);
	else
	{
		if (is_directory((proc.cmd_and_args)[0]))
			(exec_err_1((proc.cmd_and_args)[0]), exit_with_code(cshell, 126));
		if (access((proc.cmd_and_args)[0], F_OK) != 0)
			(exist_err((proc.cmd_and_args)[0]), exit_with_code(cshell, 127));
		if (access((proc.cmd_and_args)[0], X_OK) != 0)
			(perm_error((proc.cmd_and_args)[0]), exit_with_code(cshell, 126));
	}
	if ((execve((proc.cmd_and_args)[0], proc.cmd_and_args, cshell->envp)) < 0)
		(exec_err_2((proc.cmd_and_args)[0]), exit_with_code(cshell, 1));
}
