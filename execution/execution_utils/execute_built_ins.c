/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:26:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 13:07:18 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int		execute_built_ins(t_simple_command *simple_command, char ***envp, char **prompt, char *full_command)
{
	int outfile_fd = 1;
	char **commands_and_flags = ft_split(full_command, ' ');
	int **outfiles = simple_command->outfiles;
	if (simple_command->outfiles)
		outfile_fd = *((outfiles)[ft_int_array_len(outfiles) - 1]);
	if (ft_strncmp(commands_and_flags[0], "cd", 3) == 0)
		change_directory(commands_and_flags + 1, prompt, *envp);      
	else if (ft_strncmp(commands_and_flags[0], "export", 7) == 0)
		export_all_variables(commands_and_flags + 1, envp);		
	else if (ft_strncmp(commands_and_flags[0], "unset", 6) == 0)
		unset_all_variables(commands_and_flags + 1, envp);
	else if (ft_strncmp(commands_and_flags[0], "exit", 5) == 0)
	{
		ft_array_free(commands_and_flags, ft_array_len(commands_and_flags));
		exit(errno);
	}
	else if (ft_strncmp(commands_and_flags[0], "echo", 5) == 0)
		ft_echo(outfile_fd, commands_and_flags + 1);
	else if (ft_strncmp(commands_and_flags[0], "env", 4) == 0)
		print_env(outfile_fd, *envp);
	else if (ft_strncmp(commands_and_flags[0], "pwd", 4) == 0)
		ft_printf(outfile_fd, "%s\n", ft_get_cwd());
	ft_array_free(commands_and_flags, ft_array_len(commands_and_flags));
	return (errno);
}