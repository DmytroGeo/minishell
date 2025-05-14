/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:44:07 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:49 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_putnbr_fd(int n, int fd, int *count)
{
	long int	l;

	l = n;
	if (l < 0)
	{
		ft_putchar_fd('-', fd, count);
		l *= -1;
	}
	if (l >= 10)
	{
		ft_putnbr_fd(l / 10, fd, count);
		ft_putchar_fd((l % 10) + 48, fd, count);
	}
	else
		ft_putchar_fd(l + 48, fd, count);
}
