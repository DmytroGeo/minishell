/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_number_of_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:37:16 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 12:37:43 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/// find number of commands, outfiles, infiles

int find_number_of_commands(t_token *token_chain)
{
	int number_of_commands = 0;
	t_token *current_token = token_chain;
	while (!is_EOF(current_token))
	{
		if (is_command(current_token))
		{
			number_of_commands += 1;
			current_token = current_token->next;
			while (is_flag(current_token) || is_file(current_token) || is_command(current_token))
				current_token = current_token->next;         
		}
		current_token = current_token->next;
	}
	return (number_of_commands);
}

int find_number_of_outfiles(t_token *token_chain)
{
	int number_of_outfiles = 0;
	t_token *current_token = token_chain;
	
	while (!is_EOF(current_token))
	{
		if (is_redir_out(current_token))
			number_of_outfiles++;
		current_token = current_token->next;
	}
	return (number_of_outfiles);
}

int find_number_of_infiles(t_token *token_chain)
{
	int number_of_infiles = 0;
	t_token *current_token = token_chain;
	
	while (!is_EOF(current_token))
	{
		if (is_redir_in(current_token))
			number_of_infiles++;
		current_token = current_token->next;
	}
	return (number_of_infiles);
}