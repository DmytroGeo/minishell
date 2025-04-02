/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:44:07 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:12:21 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	// Arguments: int n – the integer to write, int fd – the file descriptor to write to.
	// Returns: Nothing (void function).
	// This function writes the integer 'n' to the file descriptor 'fd', converting it to a string representation and handling negative numbers.
	long int	l;

	l = n;
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l *= -1;
	}
	if (l >= 10)
	{
		ft_putnbr_fd(l / 10, fd);
		ft_putchar_fd((l % 10) + 48, fd);
	}
	else
		ft_putchar_fd(l + 48, fd);
}
