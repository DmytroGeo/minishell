/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:37:41 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "lexing.h"
#include "parsing.h"
#include "expansions.h"
#include "execution.h"
#include "minishell.h"

char	*ty(t_tok_type type)
{
	if (type == 0)
		return ("word");
	if (type == 1)
		return ("pipe");
	if (type == 2)
		return ("redir_in");
	if (type == 3)
		return ("redir_out");
	if (type == 4)
		return ("append");
	if (type == 5)
		return ("heredoc");
	return (NULL);
}

void	ft_print_tokens(t_token *head)
{
	t_token		*curr;
	int			i;

	i = 0;
	curr = head;
	while (curr)
	{
		ft_printf(2, "number: %d\n", i);
		ft_printf(2, "Value: %s\n", ((t_tok_cont *)(curr->content))->value);
		ft_printf(2, "type: %s\n", ty(((t_tok_cont *)(curr->content))->type));
		ft_printf(2, "\n", ((t_tok_cont *)(curr->content))->type);
		i++;
		curr = curr->next;
	}
}

void	run_cshell(t_cshell *cshell)
{
	int	i;

	i = wrong_number_of_quotes(cshell);
	add_history(cshell->line_read);
	if (i == 0)
	{
		lexing(cshell);
		do_all_expansions(cshell);
		init_processes(cshell);
		evaluate_and_execute(cshell);
	}
	else
	{
		cshell->exit_code = 2;
		free_cshell(cshell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cshell	cshell;

	((void)argc, (void)argv);
	init_cshell(&cshell, envp);
	init_signals();
	rl_catch_signals = 0;
	while (1)
	{
		cshell.line_read = readline(cshell.prompt);
		if (!(cshell.line_read))
			break ;
		if (*(cshell.line_read))
			run_cshell(&cshell);
		free(cshell.line_read);
	}
	(free_whole_cshell(&cshell), ft_printf(1, "exit\n"));
	return (0);
}
