/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:06:41 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/02 15:07:18 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex(unsigned int n, int fd, int *count)
{
	long int	l;

	l = n;
	if (l >= 16)
	{
		ft_puthex(l / 16, fd, count);
		if ((l % 16) >= 10)
			ft_putchar((l % 16) + 87, fd, count);
		else
			ft_putchar((l % 16) + 48, fd, count);
	}
	else if (l >= 10)
		ft_putchar(l + 87, fd, count);
	else
		ft_putchar(l + 48, fd, count);
}