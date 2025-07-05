/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 09:50:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:22:23 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_simple_command	*init_exec_struct(char *prompt, char **envp)
{
	t_simple_command	*simple_command;

	simple_command = malloc(sizeof(t_simple_command));
	if (!simple_command)
		return (NULL);
	simple_command->address_of_prompt = malloc(sizeof(char *));
	if (!(simple_command->address_of_prompt))
		return (free(simple_command), NULL);
	simple_command->address_of_prompt = &prompt;
	simple_command->address_of_envp = malloc(sizeof(char **));
	if (!(simple_command->address_of_envp))
	{
		(free(simple_command->address_of_prompt), free(simple_command));
		return (NULL);
	}
	simple_command->address_of_envp = &envp;
	return (simple_command);
}
