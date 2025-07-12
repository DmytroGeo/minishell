/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/12 12:53:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

///////////////////////

///// pre-parse to make sure everything is being followed by the correct thing

// 1. < (REDIR_IN) and << (HEREDOC) and > (REDIR_OUT) and >> (APPEND) should be followed by some word.

// 3. | (PIPE) cannot start a line.
// 4. pipe should be followed by a word or operator (< or > or << or >>).

int check_syntax(t_token *token_chain)
{
	char	*err_msg_1;
	char	*err_msg_2;

	err_msg_1 = "minishell: syntax error near unexpected token `newline'";
	err_msg_2 = "minishell: syntax error near unexpected token `|'";
	while (!is_eof(token_chain))
	{
		if (pre_parsing_condition1(token_chain))
			return(ft_printf(2, "%s\n", err_msg_1), EXIT_FAILURE);
		if (pre_parsing_condition2(token_chain))
			return (ft_printf(2, "%s\n", err_msg_2), EXIT_FAILURE);
		if (pre_parsing_condition3(token_chain))
			return(ft_printf(2, "%s\n", err_msg_2), EXIT_FAILURE);
		if (pre_parsing_condition4(token_chain))
			return(ft_printf(2, "%s\n", err_msg_2), EXIT_FAILURE);
		token_chain = token_chain->next;
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
	pipe_ptr = start;	
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

// we want to set the process equal to null 

int	init_process(t_big_struct *big_struct, int counter, t_token **start)
{
	t_proc	*proc;
	t_token *pipe_ptr;
	int infile_exit_code;
	int outfile_exit_code;

	proc = &((big_struct->proc_array)[counter]);
	pipe_ptr = find_next_pipe(*start); // finds the first (or in later cases, next) pipe (or eof)
	infile_exit_code = find_infiles(proc, *start);
	if (infile_exit_code == -1) // at least one of the infiles doesn't exist or has wrong permissions.
	{
		
	}
	//// we don't execute this process, no outfiles are created, but the rest of the processes still execute.
	else if (infile_exit_code == -2)
	{
		
	}
	outfile_exit_code = find_outfiles(proc, *start); // finds and opens all outfiles up to the first (or in later cases, next) pipe or eof and initialises the struct outfiles
	if (outfile_exit_code == -2)
	{
		
	}
	if (find_command_and_arguments(proc, *start, big_struct->envp) < 0)	// finds all commands and args up to the first (or in later cases, next) pipe or eof and initialises the struct commands and args
	/// free and exit everything
	(*start) = pipe_ptr; // move the starting pointer to the location of the pipe found
	(*start) = (*start)->next;
	return (0);	
}



////////////// initialise the array of processes in a loop:

void	init_processes(t_big_struct *big_struct, t_token *token_chain)
{
	int num_of_proc;
	int counter;

	if (check_syntax(token_chain) == EXIT_FAILURE)
		return (free_big_struct(big_struct));
	num_of_proc = find_num_of_proc(token_chain);
	big_struct->num_of_proc = num_of_proc;
	big_struct->proc_array = malloc(num_of_proc * sizeof(t_proc));
	if (!(big_struct->proc_array))
		return (free_big_struct(big_struct));
	counter = 0;
	while (counter < num_of_proc)
	{
		if (init_process(big_struct, counter, &token_chain) == -2) // something wrong with malloc so we free the big struct.
			return (free_big_struct(big_struct));	
		counter++;
	}
}


///////////////////////////////////