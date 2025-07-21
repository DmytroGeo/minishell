/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commands_and_arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:42:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 15:37:23 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	init_command(t_proc *proc, t_token *start, char **envp)
{
	t_token_content	*content;
	char			*path;

	content = (t_token_content *)(start->content);
	if (access(content->value, F_OK | X_OK) == 0 || is_builtin(content->value))
		(proc->cmd_and_args)[0] = ft_strdup(content->value);
	else
	{
		path = get_path(content->value, envp);
		if (!path)
		{
			(proc->cmd_and_args)[0] = ft_strdup(content->value);
			ft_printf(2, "%s: command not found", content->value);
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
	t_token_content	*content;

	content = (t_token_content *)(start->content);
	(proc->cmd_and_args)[counter] = ft_strdup(content->value);
	if (!((proc->cmd_and_args)[counter]))
		return (-42);
	return (0);
}

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
