/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:44:18 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 09:58:16 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	proc_call(int i, char c)
{
	int	p;

	p = 2;
	if (c == 'r' && i < 4)
	{
		ft_putstr_fd("Too few arguments\n", p, &p);
		exit(EXIT_FAILURE);
	}
	else if ((c == 'o' || c == 'i') && i < 0)
		perror(NULL);
	else if (c == 'a' && i < 0)
		perror("Can't access file");
	return (0);
}
