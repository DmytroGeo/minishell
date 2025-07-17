/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 13:10:08 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	init_setup(int **pid, int ***fd, t_main *main)
{
	int	i;
	
	i = -1;
	*pid = ft_calloc(main->num_of_proc, sizeof(int));
	if (!*pid)
		return (free_main(main), exit(1)); 
	*fd = ft_calloc(main->num_of_proc - 1, sizeof(int *));
	if (!*fd)
		return (free(pid), free_main(main), exit(1));
	while (++i < main->num_of_proc - 1)
	{
		(*fd)[i] = ft_calloc(2, sizeof(int));
		if (!(*fd)[i])
		{
			(ft_printf(2, "fd malloc failed"), free(*pid));
			(ft_array_free((void **)*fd), free_main(main), exit(1));
		}
		if (pipe((*fd)[i]) < 0)
		{
			(perror (NULL), free(*pid), close_fds(*fd, i + 1));
			(ft_array_free((void **)*fd), free_main(main), exit(1));
		}
	}
}
