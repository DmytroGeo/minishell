/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:54:35 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/02 15:15:44 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchex(unsigned int n, int fd, int *count)
{
	long int	l;

	l = n;
	if (l >= 16)
	{
		ft_putchex(l / 16, fd, count);
		if ((l % 16) >= 10)
			ft_putchar((l % 16) + 55, fd, count);
		else
			ft_putchar((l % 16) + 48, fd, count);
	}
	else if (l >= 10)
		ft_putchar(l + 55, fd, count);
	else
		ft_putchar(l + 48, fd, count);
}