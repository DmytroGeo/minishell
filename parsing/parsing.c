/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:41:55 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

///////////////////////

///// pre-parse to make sure everything is being followed by the correct thing

int pre_parse(t_token *token_chain)
{
	t_token *current_token = token_chain;
	t_token *next_token;
	while (!is_EOF(current_token))
	{
		next_token = current_token->next;
		// parse struct:
		// 1. < (REDIR_IN) should be followed by infile
		if (is_redir_in(current_token) && !is_file(next_token))
		{
			ft_printf(2, "Parse error: < should be followed by infile\n");
			return (EXIT_FAILURE);
		}
		// 2. Infile should be followed by a command or < or EOF.
		else if (is_redir_in(current_token) && is_file(next_token) && !(is_redir_out(next_token->next) || is_command(next_token->next) || is_redir_in(next_token->next) || is_EOF(next_token->next)))
		{
			ft_printf(2, "Parse error: infile should be followed by a command or < or EOF\n");
			return (EXIT_FAILURE);
		}         
		// 3. Command should be followed by < or << (heredoc) or > or | or a flag or a file (this includes commands) or an EOF
		else if (is_command(current_token) && !(is_heredoc(next_token) || is_redir_in(next_token) || is_flag(next_token) || is_command(next_token) || is_redir_out(next_token) || is_pipe(next_token) || is_file(next_token) || is_EOF(next_token)))
		{
			ft_printf(2, "Parse error: command should be followed by < or << > or | or a flag or a file\n");
			return (EXIT_FAILURE);
		}
		// 4. flags should be followed by more flags or a file or | or > or EOF
		else if (is_flag(current_token) && !(is_file(next_token) || is_redir_out(next_token) || is_pipe(next_token) || is_flag(next_token) || is_EOF(next_token)))
		{
			ft_printf(2, "Parse error: flags should be followed by more flags or a file or | or >");
			return (EXIT_FAILURE);
		}
		// 5. pipe should be followed by command
		else if (is_pipe(current_token) && !is_command(next_token))
		{
			ft_printf(2, "Parse error: pipe should be followed by command\n");
			return (EXIT_FAILURE);           
		}
		// 6. > and >> should be followed by an outfile 
		else if ((is_redir_out(current_token) || is_append(current_token)) && !is_file(next_token))
		{
			ft_printf(2, "Parse error: > or >> should be followed by an outfile\n");
			return (EXIT_FAILURE);         
		}
		// 7. Outfile should be followed by EOF or >. 
		else if ((is_redir_out(current_token) || is_append(current_token)) && is_file(next_token) && !(is_EOF(next_token->next) || is_redir_out(current_token)))
		{
			ft_printf(2, "Parse error: outfile should be followed by EOF\n");
			return (EXIT_FAILURE);
		}
		// 8. << should be followed by limiter (which can be any string)
		else if (is_heredoc(current_token) && is_EOF(next_token))
		{
			ft_printf(2, "bash: syntax error near unexpected token `newline'\n");
			return (EXIT_FAILURE);
		}
		current_token = current_token->next;
	}
	return (EXIT_SUCCESS);
}
 

/////////////////////////////////////

////////////// initialise the exec structure:

void	init_exec_struct_2(t_simple_command *simple_command, t_token *token_chain)
{
	if (pre_parse(token_chain) == EXIT_SUCCESS)
	{
		int number_of_commands = find_number_of_commands(token_chain);
		find_infiles(simple_command, token_chain);
		find_outfiles(simple_command, token_chain);
		simple_command->commands = malloc((number_of_commands + 1) * sizeof(char *));
		find_commands_and_arguments(simple_command, token_chain);
	}
	else
	{
		ft_printf(2, "There was an error parsing");
		// free what's in simple_command so far;
		return;
	}
}

///////////////////////////////////