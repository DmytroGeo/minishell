/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:33:51 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/02 16:38:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
			ft_putchar(str[n], 1, &count);
		n++;
	}
	va_end(args);
	return (count);
}
