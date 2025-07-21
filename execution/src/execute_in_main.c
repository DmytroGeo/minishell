/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:41:31 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 16:58:44 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_in_main(t_cshell *cshell)
{
	int		exit_status;
	int		outfile_fd;
	t_proc	proc;

	proc = (cshell->proc_array)[0];
	if (proc.num_outf != 0)
		outfile_fd = (proc.outfiles)[proc.num_outf - 1];
	exit_status = execute_built_ins(cshell, 0, outfile_fd);
	free_cshell(cshell);
	return (exit_status);
}
