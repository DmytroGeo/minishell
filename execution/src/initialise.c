/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 16:09:47 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	init_setup(int **pid, int ***fd, t_main *main)
{
	int	i;
	
	i = -1;
	*pid = malloc((main->num_of_proc) * sizeof(int));
	if (!*pid)
		return ; 
	*fd = malloc((main->num_of_proc - 1) * sizeof(int *));
	if (!*fd)
		return ;
	while (++i < main->num_of_proc - 1)
	{
		(*fd)[i] = malloc(2 * sizeof(int));
		if (!(*fd)[i])
		{
			(ft_printf(2, "fd malloc failed"), free(*pid));
			(ft_array_free((void **)*fd, i), free_main(main), exit(1));
		}
		if (pipe((*fd)[i]) < 0)
		{
			(perror (NULL), free(*pid), close_fds(*fd, i + 1));
			(ft_array_free((void **)*fd, i), free_main(main), exit(1));
		}
	}
}
