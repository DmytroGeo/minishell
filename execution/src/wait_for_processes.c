/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:22:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/01 13:58:31 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	wait_for_processes(int *pid, int number_of_commands)
{
	int	k;
	int	status;
	int	wpid;

	k = 0;
	while (k < number_of_commands)
	{
		wpid = waitpid(pid[k], &status, 0);
		if (wpid == -1)
			free(pid);
		k++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
