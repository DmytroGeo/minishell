/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:44:07 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:11:24 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n, int fd, int *count)
{
	long int	l;

	l = n;
	if (l < 0)
	{
		ft_putchar('-', fd, count);
		l *= -1;
	}
	if (l >= 10)
	{
		ft_putnbr(l / 10, fd, count);
		ft_putchar((l % 10) + 48, fd, count);
	}
	else
		ft_putchar(l + 48, fd, count);
}
