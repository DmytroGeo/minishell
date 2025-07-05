/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:22:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_redir_out(t_token *current_token)
{
    return (current_token->type == REDIR_OUT);
}

int is_append(t_token *current_token)
{
    return (current_token->type == APPEND);
}

void    find_outfiles(t_simple_command *simple_command, t_token *token_chain)
{
	t_token *current_token = token_chain;
	t_token *previous_token;
	int number_of_outfiles = find_number_of_outfiles(token_chain);
	int i = 0;
	simple_command->outfiles = malloc((number_of_outfiles + 1) * sizeof(int *));
	if (number_of_outfiles == 0)
	{
		simple_command->outfiles = NULL;
		return ;       
	}
	while (!is_EOF(current_token))
	{
		if ((is_redir_out(current_token) || is_append(current_token)) && is_file(current_token->next))
		{
			previous_token = current_token;
			current_token = current_token->next;
			if (access(current_token->value, F_OK) == 0)
			{
				if (access(current_token->value, W_OK) != 0)
				{
					perror("Access denied");
					return;                    
				}
			}
			else
			{
				(simple_command->outfiles)[i] = malloc(sizeof(int *));
				if (is_redir_out(previous_token))
					*((simple_command->outfiles)[i]) = open(current_token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				else if (is_append(previous_token))
					*((simple_command->outfiles)[i]) = open(current_token->value, O_CREAT | O_APPEND | O_WRONLY, 0644);                
				i++; 
			}
		}   
		current_token = current_token->next;
	}
	(simple_command->outfiles)[number_of_outfiles] = NULL;
	return;   
}