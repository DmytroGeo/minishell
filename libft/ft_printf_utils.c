/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:37:37 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/01 14:05:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_convert(int fd, char c, va_list args, int *count)
{
	if (c == '%')
		ft_putchar(c, fd, count);
	else if (c == 'c')
		ft_putchar(va_arg(args, int), fd, count);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), fd, count);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), fd, count);
	else if (c == 'x')
		ft_puthex(va_arg(args, unsigned int), fd, count);
	else if (c == 'X')
		ft_putchex(va_arg(args, unsigned int), fd, count);
	else if (c == 'u')
		ft_putuns(va_arg(args, unsigned int), fd, count);
	else if (c == 'p')
		ft_putptr(va_arg(args, void *), fd, count);
}
