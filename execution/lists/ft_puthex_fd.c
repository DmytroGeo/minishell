/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:55:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:47 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_puthex_fd(unsigned int n, int fd, int *count)
{
	long int	l;

	l = n;
	if (l >= 16)
	{
		ft_puthex_fd(l / 16, fd, count);
		if ((l % 16) >= 10)
			ft_putchar_fd((l % 16) + 87, fd, count);
		else
			ft_putchar_fd((l % 16) + 48, fd, count);
	}
	else if (l >= 10)
		ft_putchar_fd(l + 87, fd, count);
	else
		ft_putchar_fd(l + 48, fd, count);
}
