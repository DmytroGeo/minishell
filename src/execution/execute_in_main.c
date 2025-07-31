/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:41:31 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 11:58:25 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	execute_in_main(t_cshell *cshell)
{
	int		outfile_fd;
	int		infile_fd;
	t_proc	proc;

	outfile_fd = STDOUT_FILENO;
	infile_fd = STDIN_FILENO;
	proc = (cshell->proc_array)[0];
	if (proc.num_outf != 0)
		outfile_fd = (proc.outfiles)[proc.num_outf - 1];
	if (proc.num_inf != 0)
		infile_fd = (proc.infiles)[proc.num_inf - 1];
	if (outfile_fd < 0 || infile_fd < 0)
		cshell->exec_code = 1;
	else
		execute_built_ins(cshell, 0, outfile_fd);
	free_proc_array(cshell->proc_array, cshell->num_of_proc);
	cshell->proc_array = NULL;
	free_tok_chain(&(cshell->token_chain), del_tok_cont);
	cshell->token_chain = NULL;
}
