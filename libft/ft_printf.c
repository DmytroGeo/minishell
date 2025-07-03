/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:33:51 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/01 14:09:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(int fd, const char *str, ...)
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
			ft_convert(fd, str[n], args, &count);
		}
		else
			ft_putchar(str[n], fd, &count);
		n++;
	}
	va_end(args);
	return (count);
}
