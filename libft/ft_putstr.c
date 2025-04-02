/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:29:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/02 15:16:14 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *s, int fd, int *count)
{
	size_t	n;

	n = 0;
	if (s == NULL)
	{
		*count += write(fd, "(null)", 6);
		return ;
	}
	while (s[n])
	{
		ft_putchar(s[n], fd, count);
		n++;
	}
}