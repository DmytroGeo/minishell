/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/13 13:27:05 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

/**
 * @param tok_chain a pointer to the head of the token chain.
 * @return 0 if no syntax errors and 1 if syntax errors detected
 * @brief Goes through the token chain and sees if
 *  any of the follwoing rules are broken:
 * 1. < (REDIR_IN) and << (HEREDOC) and 
 * > (REDIR_OUT) and >> (APPEND) should be followed by some word.
 * 2. | (PIPE) cannot start a line.
 * 3. pipe should be followed by a word or redirect operator
 * (< or > or << or >>).
 * 4. pipe cannot end a line.
 * see (src->parsing->synax_conditions.c)
 */
int	check_syntax(t_token *tok_chain)
{
	char	*err_msg_2;
	char	*opr;

	err_msg_2 = "minishell: syntax error near unexpected token `|'";
	while (tok_chain)
	{
		if (syntax_check_1(tok_chain))
		{
			opr = ((t_tok_cont *)(tok_chain->content))->value;
			ft_printf(2, "minishell: %s should be followed by a word\n", opr);
			return (1);
		}
		if (syntax_check_2(tok_chain))
			return (ft_printf(2, "%s\n", err_msg_2), 1);
		if (syntax_check_3(tok_chain))
			return (ft_printf(2, "%s\n", err_msg_2), 1);
		if (syntax_check_4(tok_chain))
			return (ft_printf(2, "%s\n", err_msg_2), 1);
		tok_chain = tok_chain->next;
	}
	return (EXIT_SUCCESS);
}

t_token	*find_next_pipe(t_token *start)
{
	t_token	*pipe_ptr;

	pipe_ptr = NULL;
	while (start)
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

int	find_num_of_proc(t_token *tok_chain)
{
	int	number_of_pipes;

	number_of_pipes = 0;
	while (tok_chain)
	{
		if (is_pipe(tok_chain))
			number_of_pipes += 1;
		tok_chain = tok_chain->next;
	}
	return (number_of_pipes + 1);
}

/**
 * @param cshell The main 'cshell' structure.
 * @param counter The number of the current process.
 * @param address_of_start The address of the current token.
 * @return 0 in the case of success, -42 if memory allocation fails.
 * @brief This function initialises the infiles, outfiles and commands
 * and arguments of each process. It also stores a poiner to the next pipe,
 * which it moves after it initialises each process. This is because,
 * as mentioned earlier, each process has its own infiles, outfiles, 
 * etc. which are delimited by pipes.
 */
int	init_process(t_cshell *cshell, int counter, t_token **address_of_start)
{
	t_proc	*proc;
	t_token	*pipe_ptr;
	int		exit_code;

	proc = &(cshell->proc_array)[counter];
	pipe_ptr = find_next_pipe(*address_of_start);
	exit_code = find_infiles_and_outfiles(proc, *address_of_start);
	if (exit_code == -42)
		return (exit_code);
	exit_code = find_cmd_and_args(proc, *address_of_start, cshell->envp);
	if (exit_code == -42)
		return (exit_code);
	if (pipe_ptr)
		(*address_of_start) = pipe_ptr->next;
	return (0);
}

/**
 * @param cshell The main 'cshell' structure.
 * @return nothing - this is a void function
 * @brief This function initialises the process array by initialising 
 * processes in a loop. The definition of a
 * process is a a part of the line read line that has its own command,
 * arguments, infiles and outfiles. Processes are delimited by pipes.
 * Example: in the line:
 * < in1 cat | echo hello > out | pwd.
 * There are three processes: 1) < in cat
 * 2) echo hello > out
 * 3) pwd.
 */
void	init_processes(t_cshell *cshell)
{
	int		counter;
	t_token	*copy_of_start;

	if (check_syntax(cshell->token_chain) || cshell->parse_code == 2)
	{
		cshell->parse_code = 2;
		return ;
	}
	cshell->num_of_proc = find_num_of_proc(cshell->token_chain);
	cshell->proc_array = ft_calloc(cshell->num_of_proc, sizeof(t_proc));
	if (!(cshell->proc_array))
		(free_whole_cshell(cshell), exit(-42));
	counter = -1;
	copy_of_start = cshell->token_chain;
	while (++counter < cshell->num_of_proc)
	{
		if (init_process(cshell, counter, &copy_of_start) == -42)
			(free_whole_cshell(cshell), exit(-42));
	}
}
