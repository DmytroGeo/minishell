/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 16:35:33 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

///////////////////////

///// pre-parse to make sure everything is being followed by the correct thing

// 1. < (REDIR_IN) and << (HEREDOC) and 
// > (REDIR_OUT) and >> (APPEND) should be followed by some word.

// 2. | (PIPE) cannot start a line.

// 3. pipe should be followed by a word or redirect operator
// (< or > or << or >>).

// 4. pipe cannot end a line.

int check_syntax(t_token *tok_chain)
{
	char	*err_msg_2;
	char	*opr;

	err_msg_2 = "minishell: syntax error near unexpected token `|'";
	while (!is_eof(tok_chain))
	{
		if (syntax_check_1(tok_chain))
		{
			opr = ((t_token_content *)(tok_chain->content))->value;
			ft_printf(2, "minishell: %s should be followed by a word\n", opr);
			return (1);
		}
		if (syntax_check_2(tok_chain))
			return (ft_printf(2, "%s\n", err_msg_2), 1);
		if (syntax_check_3(tok_chain))
			return(ft_printf(2, "%s\n", err_msg_2), 1);
		if (syntax_check_4(tok_chain))
			return(ft_printf(2, "%s\n", err_msg_2), 1);
		tok_chain = tok_chain->next;
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

int find_num_of_proc(t_token *tok_chain)
{
	int number_of_pipes;

	number_of_pipes = 0;
	while (!is_eof(tok_chain))
	{
		if (is_pipe(tok_chain))
			number_of_pipes += 1;
		tok_chain = tok_chain->next;
	}
	return (number_of_pipes + 1);
}

int	init_process(t_main *main, int counter, t_token **address_of_start)
{
	t_proc	proc;
	t_token *pipe_ptr;
	int exit_code;

	proc = (main->proc_array)[counter];
	proc.cmd_and_args = NULL;
	proc.infiles = NULL;
	proc.outfiles = NULL;	
	pipe_ptr = find_next_pipe(*address_of_start); // finds the first (or in later cases, next) pipe (or eof)
	exit_code = find_infiles(&proc, *address_of_start);
	if (exit_code == -42) // if malloc goes wrong
		return (exit_code);
	exit_code = find_outfiles(&proc, *address_of_start);
	if (exit_code == -42) // if malloc goes_wrong
		return (exit_code);
	exit_code = find_cmd_and_args(&proc, *address_of_start, main->envp);
	if (exit_code == -42) // if malloc goes_wrong
		return (exit_code);
	(*address_of_start) = pipe_ptr->next; // move the start pointer to token after the next pipe
	return (0);	
}



////////////// initialise the array of processes in a loop:

void	init_processes(t_main *main, int *exit_code_addr)
{
	int counter;
	t_token *copy_of_start;

	if (check_syntax(main->token_chain) == EXIT_FAILURE)
	{
		*exit_code_addr = 2;
		return (free_main(main));		
	}
	main->num_of_proc = find_num_of_proc(main->token_chain);
	main->proc_array = ft_calloc(main->num_of_proc, sizeof(t_proc));
	if (!(main->proc_array))
	{
		*exit_code_addr = -42;
		return (free_main(main));		
	}
	counter = -1;
	copy_of_start = main->token_chain;
	while (++counter < main->num_of_proc)
	{
		if (init_process(main, counter, &copy_of_start) == -42)
		{
			*exit_code_addr = -42;
			return (free_main(main));		
		}
	}
}

///////////////////////////////////