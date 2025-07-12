/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commands_and_arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:42:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 18:20:27 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		find_number_of_commands_and_args(t_token *start)
{
	int	number_of_commands_and_args;
	char *file_name;
	
	number_of_commands_and_args = 0;
	while (!is_eof(start) && !is_pipe(start))
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

int		init_command(t_proc *proc_struct, t_token *start, char **envp)
{
	t_token_content *content;
	char *path;

	content = (t_token_content *)(start->content);

	if (access(content->value, F_OK | X_OK) == 0)
		(proc_struct->cmd_and_args)[0] = ft_strdup(content->value);
	else
	{
		path = get_path(content->value, envp);
		if (!path)
			(proc_struct->cmd_and_args)[0] = ft_strdup(content->value);
		else
			(proc_struct->cmd_and_args)[0] = path;	
	}

	if (!((proc_struct->cmd_and_args)[0]))
		return (-1);
	return (0);
}

int		init_arg(t_proc *proc_struct, t_token *start, int counter)
{
	t_token_content *content;

	content = (t_token_content *)(start->content);
	(proc_struct->cmd_and_args)[counter] = ft_strdup(content->value);
	if (!((proc_struct->cmd_and_args)[counter]))
		return (-1);
	return (0);
}

int    find_command_and_arguments(t_proc *proc_struct, t_token *start, char **envp)
{
	int counter;
	int num_cmd_args;

	counter = 0;
	num_cmd_args = find_number_of_commands_and_args(start);
	proc_struct->cmd_and_args = malloc((num_cmd_args + 1) * sizeof(char *));
	if (!(proc_struct->cmd_and_args))
		return (-1);
	while (counter < num_cmd_args)
	{
		if (is_redirect(start))
			start = start->next->next;
		else
		{
			if (counter == 0 && init_command(proc_struct, start, envp) < 0)
				return (free(proc_struct->cmd_and_args), -1);
			else if (counter != 0 && init_arg(proc_struct, start, counter) < 0)
				return (ft_array_free(proc_struct->cmd_and_args, num_cmd_args), -1);
			counter++;
			start = start->next;
		}
	}
	(proc_struct->cmd_and_args)[counter] = NULL;
	return (0);
}