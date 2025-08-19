/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:39:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:15:56 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
/**
 * @brief This functions closes 'len' number of pipes, 
 * closing their read and write ends.
 * @param fd The array of pipes.
 * @param len The number of pipes we want to close.
 * @return void function
 */
void	close_pipes(int **fd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return ;
}
