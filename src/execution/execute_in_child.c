/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:48:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:37:59 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	exit_with_code(t_cshell *cshell, int i)
{
	cshell->exit_code = i;
	(free_whole_cshell(cshell), exit(cshell->exit_code));
}

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
	if (access((proc.cmd_and_args)[0], F_OK | X_OK) != 0)
		exit_with_code(cshell, 127);
	if ((execve((proc.cmd_and_args)[0], proc.cmd_and_args, cshell->envp)) < 0)
		exit_with_code(cshell, 1);
}
