/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_commands_and_arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:42:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:19:51 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_command(t_token *current_token)
{
    if (!is_EOF(current_token))
    {
        return (is_built_in(current_token->value) || (current_token->path != NULL));
    }
    return(false);
}

int is_flag(t_token *current_token)
{
    return (current_token->type == FLAG);
}

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

void    find_commands_and_arguments(t_simple_command *simple_command, t_token *token_chain)
{
	t_token *current_token = token_chain;
	int counter = 0;
	while (!is_EOF(current_token))
	{
		if (is_command(current_token))
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