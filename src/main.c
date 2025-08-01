/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/01 09:00:16 by dgeorgiy         ###   ########.fr       */
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
	add_history(cshell->line_read);
	lexing(cshell);
	do_all_expansions(cshell);
	init_processes(cshell);
	evaluate_and_execute(cshell);
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
