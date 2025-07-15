/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 15:47:55 by dgeorgiy         ###   ########.fr       */
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
	char	*oper;

	err_msg_2 = "minishell: syntax error near unexpected token `|'";
	while (!is_eof(tok_chain))
	{
		if (syntax_check_1(tok_chain))
		{
			oper = ((t_token_content *)(tok_chain->content))->value;
			ft_printf(2, "minishell: %s should be followed by a word\n", oper);
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
	t_proc	*address_of_proc;
	t_token *pipe_ptr;
	int infile_exit_code;
	int outfile_exit_code;
	int cmd_and_args_exit_code;

	address_of_proc = &((main->proc_array)[counter]);
	pipe_ptr = find_next_pipe(*address_of_start); // finds the first (or in later cases, next) pipe (or eof)
	infile_exit_code = find_infiles(address_of_proc, *address_of_start);
	if (infile_exit_code == -1 || infile_exit_code == -2) // at least one of the infiles doesn't exist or has wrong permissions.
		return (infile_exit_code);
	outfile_exit_code = find_outfiles(address_of_proc, *address_of_start); // finds and opens all outfiles up to the first (or in later cases, next) pipe or eof and initialises the struct outfiles
	if (outfile_exit_code == -1 || outfile_exit_code == -2)
		return (outfile_exit_code);
	cmd_and_args_exit_code = find_cmd_and_args(address_of_proc, *address_of_start, main->envp);
	if (cmd_and_args_exit_code == -1 || cmd_and_args_exit_code == -2)
		return (outfile_exit_code);
	(*address_of_start) = pipe_ptr; // move the starting pointer to the location of the pipe found
	(*address_of_start) = (*address_of_start)->next;
	return (0);	
}



////////////// initialise the array of processes in a loop:

void	init_processes(t_main *main, t_token *tok_chain)
{
	int counter;
	t_token *copy_of_start;

	if (check_syntax(tok_chain) == EXIT_FAILURE)
		return (free_main(main), free_tok_chain(&tok_chain, del_tok_cont));
	main->num_of_proc = find_num_of_proc(tok_chain);
	main->proc_array = malloc(main->num_of_proc * sizeof(t_proc));
	if (!(main->proc_array))
		return (free_main(main), free_tok_chain(&tok_chain, del_tok_cont));
	counter = 0;
	copy_of_start = tok_chain;
	while (counter < main->num_of_proc)
	{
		if (init_process(main, counter, &tok_chain) == -2)
			return (free_main(main), free_tok_chain(&tok_chain, del_tok_cont)); // we need a case for if we get -1 (i.e) unidentified command, arg, wrong permissions for outfile or infile
		counter++;
	}
}


///////////////////////////////////