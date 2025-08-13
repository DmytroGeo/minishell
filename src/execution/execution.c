/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/13 15:49:02 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "signals.h"

/**
 * @brief This function checks whether parsing encountered any syntax errors.
 * If it did encounter any parsing errors, it sets the (exit_code)
 * to the parse code and then the parse_code to 0 and frees and exits.
 * Otherwise, it runs execution.
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	evaluate_and_execute(t_cshell *cshell)
{
	if (cshell->parse_code == 0)
		return (execution(cshell));
	cshell->exit_code = cshell->parse_code;
	cshell->parse_code = 0;
	return (free_cshell(cshell));
}

/**
 * @brief This function is the execution part of minishell.
 * If we have exactly one process AND the command is a built-in, we run 
 * execute in main. Otherwise, we go through init setup, process loop,
 * close fds and wait for processes.
 * Then we free all parts of the cshell apart from the prompt and envp.
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	execution(t_cshell *cshell)
{
	char	*first_command;

	first_command = ((cshell->proc_array)[0]).cmd_and_args[0];
	if (cshell->num_of_proc == 1 && is_builtin(first_command))
		return (execute_in_main(cshell));
	signal(SIGINT, SIG_IGN);
	initialise_pipes(cshell);
	process_loop(cshell);
	close_pipes(cshell->fd, cshell->num_of_proc - 1);
	wait_for_processes(cshell);
	signal(SIGINT, handle_sigint);	
	free_cshell(cshell);
}
