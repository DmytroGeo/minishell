/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:29:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:34:55 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_and_exit(int *pid, int **fd, t_simple_command *simple_command)
{
	int		number_of_commands;
	int		exit_status;
	if (!fd)
		return ;
	number_of_commands = ft_array_len(simple_command->commands);
	exit_status = free_simple_command(simple_command);
	free(pid);
	ft_intarr_free(fd, number_of_commands - 1);
	return ;
}
