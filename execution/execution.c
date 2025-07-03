/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:19:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 18:58:00 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

int	execution(t_simple_command *simple_command, char ***envp, char **address_of_prompt)
{
	int		exit_status;

	if (ft_array_len(simple_command->commands) == 1 && check_built_ins(simple_command) == 1)
	{
		execute_built_ins_in_main(simple_command, envp, address_of_prompt);
		return(errno);
	}
	init_list(simple_command, simple_command->commands, *envp);
	init_setup(&pid, &fd, simple_command);
	process_loop(pid, fd, simple_command);
	close_fds(fd, ft_array_len(simple_command->commands) - 1);
	/* I have to free t_simple_command*/
	ft_intarr_free(fd, ft_array_len(simple_command->commands) - 1);
	exit_status = wait_for_processes(pid, ft_array_len(simple_command->commands));
	free(pid);
	return (exit_status);
}
    // ft_printf("From execution, the prompt is %s\n", simple_command->prompt);
	// ft_printf("The number of commands is %d\n", number_of_commands);
	// char **cur = simple_command->commands;
	// while (*cur)
	// {
	// 	ft_printf("The command is %s\n", *cur);
	// 	cur++;          
	// }