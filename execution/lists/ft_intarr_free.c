/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:45:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_intarr_free(int **fd, int len)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	while (i < len)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
