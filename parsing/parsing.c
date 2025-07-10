/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/10 15:35:48 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

///////////////////////

///// pre-parse to make sure everything is being followed by the correct thing

// 1. < (REDIR_IN) and << (HEREDOC) should be followed by some word.
// 2. > (REDIR_OUT) and >> (APPEND) should be followed by some word.
// 3. | (PIPE) cannot start a line.
// 4. pipe should be followed by a word or operator (< or > or << or >>).

int pre_parse(t_token *token_chain)
{
	t_token *current_token;
	t_token *previous_token;
	t_token *next_token;
	char	*err_msg_1;
	char	*err_msg_2;

	current_token = token_chain;
	err_msg_1 = "minishell: syntax error near unexpected token `newline'";
	err_msg_2 = "minishell: syntax error near unexpected token `|'";
	while (!is_eof(current_token))
	{
		next_token = current_token->next;
		previous_token = current_token->previous;
		if ((is_redir_in(current_token) || is_heredoc(current_token)) && !is_word(next_token))
			return(ft_printf(2, "%s\n", err_msg_1), EXIT_FAILURE);
		if ((is_redir_out(current_token) || is_append(current_token)) && !is_word(next_token))
			return (ft_printf(2, "%s\n", err_msg_1), EXIT_FAILURE);
		if (is_pipe(current_token) && !previous_token)
			return (ft_printf(2, "%s\n", err_msg_2), EXIT_FAILURE);
		if (is_pipe(current_token) && !(is_word(next_token) || is_operator(next_token)))
			return(ft_printf(2, "%s\n", err_msg_2), EXIT_FAILURE);
		current_token = current_token->next;
	}
	return (EXIT_SUCCESS);
}

////////

////// find and returns a pointer to the next pipe:

t_token *find_next_pipe(t_token *start)
{
	t_token *pipe_ptr;

	pipe_ptr = NULL;
	while (!is_eof(start))
	{
		if (is_pipe(start))
		{
			pipe_ptr = start;
			return (pipe_ptr);
		}
		start = start->next;
	}
	return (pipe_ptr);
}

////////////////////
// finds the number of processes. this is always one more than the number of pipes.
///////

int find_num_of_proc(t_token *token_chain)
{
	int number_of_pipes;

	number_of_pipes = 0;
	while (!is_eof(token_chain))
	{
		if (is_pipe(token_chain))
			number_of_pipes += 1;
		token_chain = token_chain->next;
	}
	return (number_of_pipes + 1);
}

////////////// initialise the exec structure:

void	init_processes(t_big_struct *big_struct, t_token *token_chain)
{
	t_token *start;
	t_token *pipe_ptr;
	t_proc_struct *proc_struct;
	int num_of_proc;
	int counter;

	pipe_ptr = NULL;
	if (pre_parse(token_chain) == EXIT_FAILURE)
	{
		free(big_struct);
		// free_token(chain)
		return ;		
	}
	else
	{
		num_of_proc = find_num_of_proc(token_chain);
		big_struct->num_of_proc = num_of_proc;
		big_struct->proc_array = malloc(num_of_proc * sizeof(t_proc_struct));
		if (!big_struct->proc_array)
		{
			// free everything
		}
		counter = 0;
		start = token_chain;
		while (counter < num_of_proc)
		{
			proc_struct = &((big_struct->proc_array)[counter]);
			pipe_ptr = find_next_pipe(start); // finds the first (or in later cases, next) pipe (or eof)
			if (find_infiles(proc_struct, start) < 0) // finds and opens all infiles up to the first (or in later cases, next) pipe or eof and initialises the struct infiles
				//// free and exit everything 
			find_outfiles(proc_struct, start); // finds and opens all outfiles up to the first (or in later cases, next) pipe or eof and initialises the struct outfiles
			find_command_and_arguments(proc_struct, start); // finds all commands and args up to the first (or in later cases, next) pipe or eof and initialises the struct commands and args
			start = pipe_ptr; // move the starting pointer to the location of the pipe found
			start = start->next;
			counter++;	
		}
	}
}


///////////////////////////////////