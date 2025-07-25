/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:10:18 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	init_setup(t_cshell *cshell)
{
	int	i;

	i = -1;
	cshell->pid = ft_calloc(cshell->num_of_proc, sizeof(int));
	if (!cshell->pid)
		return (free_whole_cshell(cshell), exit(1));
	cshell->fd = ft_calloc(cshell->num_of_proc - 1, sizeof(int *));
	if (!cshell->fd)
		return (free_whole_cshell(cshell), exit(1));
	while (++i < cshell->num_of_proc - 1)
	{
		(cshell->fd)[i] = ft_calloc(2, sizeof(int));
		if (!(cshell->fd)[i])
			(free_whole_cshell(cshell), exit(1));
		if (pipe((cshell->fd)[i]) < 0)
		{
			(perror(NULL), close_fds(cshell->fd, i + 1));
			(free_whole_cshell(cshell), exit(1));
		}
	}
}
