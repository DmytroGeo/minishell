/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:26:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/10 15:35:09 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int		execute_built_ins(t_big_struct *big_struct, int i, int *pid, int **fd)
{
	t_proc_struct process;
	int		outfile_fd;
	
	process = big_struct->proc_array[i];
	outfile_fd = *((process.outfiles)[ft_int_array_len(process.outfiles) - 1]);
	if (ft_strncmp(commands_and_arguments[0], "cd", 3) == 0)
		exit_code = change_directory(commands_and_arguments + 1, simple_command->address_of_prompt, simple_command->address_of_envp);      
	else if (ft_strncmp(commands_and_arguments[0], "export", 7) == 0)
		exit_code = export_all_variables(commands_and_arguments + 1, simple_command->address_of_envp);		
	else if (ft_strncmp(commands_and_arguments[0], "unset", 6) == 0)
		exit_code = unset_all_variables(commands_and_arguments + 1, simple_command->address_of_envp);
	else if (ft_strncmp(commands_and_arguments[0], "exit", 5) == 0)
		exit_code = ft_exit(commands_and_arguments, pid, fd, simple_command);
	else if (ft_strncmp(commands_and_arguments[0], "echo", 5) == 0)
		exit_code = ft_echo(outfile_fd, commands_and_arguments + 1);
	else if (ft_strncmp(commands_and_arguments[0], "env", 4) == 0)
		exit_code = print_envp(outfile_fd, *(simple_command->address_of_envp));		
	else if (ft_strncmp(commands_and_arguments[0], "pwd", 4) == 0)
		ft_printf(outfile_fd, "%s\n", ft_get_cwd());
	ft_array_free(commands_and_arguments, ft_array_len(commands_and_arguments));
	return (exit_code);
}