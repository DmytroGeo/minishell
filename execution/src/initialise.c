/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 10:58:04 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	init_setup(int **pid, int ***fd, t_simple_command *simple_command)
{
	int	i;
	int number_of_commands = ft_array_len(simple_command->commands);
	i = -1;
	*pid = malloc((number_of_commands) * sizeof(int));
	if (!*pid)
		return ;
	else 
		*fd = malloc((number_of_commands - 1) * sizeof(int *));
	if (!*fd)
		return ;
	while (++i < number_of_commands - 1)
	{
		(*fd)[i] = malloc(2 * sizeof(int));
		if (!(*fd)[i])
		{
			perror("fd malloc failed");
			(free(*pid), ft_intarr_free(*fd, i), free_simple_command(simple_command));
			exit (EXIT_FAILURE);
		}
		if (pipe((*fd)[i]) < 0)
		{
			(perror (NULL), free(*pid));
			(close_fds(*fd, i + 1), ft_intarr_free(*fd, i), free_simple_command(simple_command));
			exit (EXIT_FAILURE);
		}
	}
}
