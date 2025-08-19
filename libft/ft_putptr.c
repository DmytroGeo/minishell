/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:43:12 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:10:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex2(unsigned long int n, int fd, int *count)
{
	unsigned long int	l;

	l = n;
	if (l >= 16)
	{
		ft_puthex2(l / 16, fd, count);
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

void	ft_putptr(void *ptr, int fd, int *count)
{
	unsigned long int	l;

	l = (unsigned long int)ptr;
	if (ptr == 0)
		ft_putstr("(nil)", fd, count);
	else
	{
		ft_putstr("0x", fd, count);
		ft_puthex2(l, fd, count);
	}
}
