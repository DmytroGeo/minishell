/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:33:51 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_convert(char c, va_list args, int *count)
{
	if (c == '%')
		ft_putchar_fd(c, 1, count);
	else if (c == 'c')
		ft_putchar_fd(va_arg(args, int), 1, count);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(args, int), 1, count);
	else if (c == 's')
		ft_putstr_fd(va_arg(args, char *), 1, count);
	else if (c == 'x')
		ft_puthex_fd(va_arg(args, unsigned int), 1, count);
	else if (c == 'X')
		ft_putchex_fd(va_arg(args, unsigned int), 1, count);
	else if (c == 'u')
		ft_putuns_fd(va_arg(args, unsigned int), 1, count);
	else if (c == 'p')
		ft_putptr_fd(va_arg(args, void *), 1, count);
}

int	ft_printf(const char *str, ...)
{
	int		n;
	int		count;
	va_list	args;

	va_start(args, str);
	n = 0;
	count = 0;
	while (str[n] != '\0')
	{
		if (str[n] == '%')
		{
			n++;
			ft_convert(str[n], args, &count);
		}
		else
			ft_putchar_fd(str[n], 1, &count);
		n++;
	}
	va_end(args);
	return (count);
}
