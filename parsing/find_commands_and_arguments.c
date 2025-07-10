/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commands_and_arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:42:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/09 13:55:41 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    collect_arguments(t_token **current_token, t_simple_command *simple_command, int counter)
{
	char *temp = NULL;
	while (is_flag(*current_token) || is_file(*current_token) || is_command(*current_token))
	{
		temp = ft_strjoin((simple_command->commands)[counter], " ");
		free((simple_command->commands)[counter]);
		(simple_command->commands)[counter] = temp;
		temp = ft_strjoin((simple_command->commands)[counter], (*current_token)->value);
		free((simple_command->commands)[counter]);
		(simple_command->commands)[counter] = temp;
		(*current_token) = (*current_token)->next;               
	}
}

void    find_command_and_arguments(t_simple_command *simple_command, t_token **token_chain)
{
	t_token *current_token;
	int counter;
	int number_of_commands;

	number_of_commands = find_number_of_commands(token_chain);
	current_token = token_chain;
	counter = 0;
	simple_command->commands = malloc((number_of_commands + 1) * sizeof(char *));
	while (!is_eof(current_token))
	{
		if (is_word(current_token))
		{
			(simple_command->commands)[counter] = ft_strdup(current_token->value);
			current_token = current_token->next;
			if (is_flag(current_token) || is_file(current_token) || is_command(current_token))
				collect_arguments(&current_token, simple_command, counter);// here we're passing the address of current token because we want to skip it to the end of the flags
			counter++;
		}
		else
			current_token = current_token->next;
	}
	(simple_command->commands)[counter] = NULL;
	return ;
}