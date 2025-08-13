/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/12 12:58:21 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "lexing.h"
#include "parsing.h"
#include "expansions.h"
#include "execution.h"
#include "minishell.h"

void	run_cshell(t_cshell *cshell)
{
	int	i;

	i = wrong_number_of_quotes(cshell);
	add_history(cshell->line_read);
	if (i == 0)
	{
		lexing(cshell);
		do_all_expansions(cshell);
		if (!(cshell->token_chain))
			return (free_cshell(cshell));
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
