/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:26:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 13:11:33 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int		execute_built_ins(t_cshell *cshell, int i)
{
	t_proc proc;
	char **cmd_and_args;
	int		outfile_fd;
	int		exit_code;
	
	proc = cshell->proc_array[i];
	outfile_fd = (proc.outfiles)[proc.num_outf - 1];
	cmd_and_args = proc.cmd_and_args;
	exit_code = 0;
	if (ft_strncmp(cmd_and_args[0], "cd", 3) == 0)
		exit_code = ft_chdir(cmd_and_args + 1, &(cshell->prompt), &(cshell->envp));
	else if (ft_strncmp(cmd_and_args[0], "export", 7) == 0)
		exit_code = export_all_variables(cmd_and_args + 1, &(cshell->envp));		
	else if (ft_strncmp(cmd_and_args[0], "unset", 6) == 0)
		exit_code = unset_all_variables(cmd_and_args + 1, &(cshell->envp));
	else if (ft_strncmp(cmd_and_args[0], "exit", 5) == 0)
		exit_code = ft_exit(cmd_and_args, cshell);
	else if (ft_strncmp(cmd_and_args[0], "echo", 5) == 0)
		exit_code = ft_echo(outfile_fd, cmd_and_args + 1);
	else if (ft_strncmp(cmd_and_args[0], "env", 4) == 0)
		exit_code = print_envp(outfile_fd, cshell->envp);		
	else if (ft_strncmp(cmd_and_args[0], "pwd", 4) == 0)
		ft_printf(outfile_fd, "%s\n", ft_get_cwd());
	return (exit_code);
}