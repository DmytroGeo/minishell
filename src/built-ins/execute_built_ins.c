/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:26:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/06 17:32:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_built_ins(t_cshell *cshell, int i, int outfile_fd)
{
	t_proc	proc;

	proc = cshell->proc_array[i];
	if (!proc.cmd_and_args)
		return ;
	else if (ft_strncmp(proc.cmd_and_args[0], "cd", 3) == 0)
		ft_chdir(proc.cmd_and_args + 1, cshell);
	else if (ft_strncmp(proc.cmd_and_args[0], "export", 7) == 0)
		export_all_vars(proc.cmd_and_args + 1, cshell, outfile_fd);
	else if (ft_strncmp(proc.cmd_and_args[0], "unset", 6) == 0)
		unset_all_vars(proc.cmd_and_args + 1, cshell);
	else if (ft_strncmp(proc.cmd_and_args[0], "exit", 5) == 0)
		ft_exit(proc.cmd_and_args, cshell);
	else if (ft_strncmp(proc.cmd_and_args[0], "echo", 5) == 0)
		ft_echo(outfile_fd, proc.cmd_and_args + 1, cshell);
	else if (ft_strncmp(proc.cmd_and_args[0], "env", 4) == 0)
		print_envp(outfile_fd, cshell->envp);
	else if (ft_strncmp(proc.cmd_and_args[0], "pwd", 4) == 0)
		ft_pwd(outfile_fd);
}
