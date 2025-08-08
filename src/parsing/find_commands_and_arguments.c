/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commands_and_arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:42:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 21:05:16 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	find_number_of_commands_and_args(t_token *start)
{
	int	number_of_commands_and_args;

	number_of_commands_and_args = 0;
	while (start && !is_pipe(start))
	{
		if (is_redirect(start))
			start = start->next->next;
		else
		{
			number_of_commands_and_args++;
			start = start->next;
		}
	}
	return (number_of_commands_and_args);
}

/**
 * @brief AN important thing to note about this functions is
 * that 1) if our command can be found in $PATH (example, cat), 
 * we strdup its whole path.
 * For all other cases (built-in, command not found, full path given),
 * we just strdup the string.
 * @param start The start of our token chain
 * @param proc The address of our current proc structure.
 * @param envp our copy of envp.
 * @return 0 on success, -42 on failed memory allocation.
 */
int	init_command(t_proc *proc, t_token *start, char **envp)
{
	t_tok_cont	*content;
	char		*path;

	content = (t_tok_cont *)(start->content);
	if (access(content->value, F_OK | X_OK) == 0 || is_builtin(content->value))
		(proc->cmd_and_args)[0] = ft_strdup(content->value);
	else
	{
		path = get_path(content->value, envp);
		if (!path)
		{
			(proc->cmd_and_args)[0] = ft_strdup(content->value);
			ft_printf(2, "%s: command not found\n", content->value);
		}
		else
			(proc->cmd_and_args)[0] = path;
	}
	if (!((proc->cmd_and_args)[0]))
		return (-42);
	return (0);
}

int	init_arg(t_proc *proc, t_token *start, int counter)
{
	t_tok_cont	*content;

	content = (t_tok_cont *)(start->content);
	(proc->cmd_and_args)[counter] = ft_strdup(content->value);
	if (!((proc->cmd_and_args)[counter]))
		return (-42);
	return (0);
}

/**
 * @brief This function initialises the char ** cmd_and_args
 * attribute of the current proc struct.
 * The command of a process is defined as the first string that
 * does not follow a redirection operator (<, >, <<, >>).
 * The arguments of that command are strings in the same process
 * that come after the command and aren't proceeded by a redirection
 * operator.
 * @param start The start of our token chain
 * @param proc The address of our current proc structure.
 * @param envp our copy of envp.
 * @return 0 on success, -42 on failed memory allocation.
 */
int	find_cmd_and_args(t_proc *proc, t_token *start, char **envp)
{
	int	counter;
	int	num_cmd_args;

	counter = 0;
	num_cmd_args = find_number_of_commands_and_args(start);
	proc->cmd_and_args = ft_calloc((num_cmd_args + 1), sizeof(char *));
	if (!(proc->cmd_and_args))
		return (-42);
	while (counter < num_cmd_args)
	{
		if (is_redirect(start))
			start = start->next->next;
		else
		{
			if (counter == 0 && init_command(proc, start, envp) == -42)
				return (-42);
			else if (counter != 0 && init_arg(proc, start, counter) == -42)
				return (-42);
			counter++;
			start = start->next;
		}
	}
	return (0);
}
