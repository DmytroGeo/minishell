/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:15:16 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/02 15:09:59 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putuns(unsigned int n, int fd, int *count)
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
		ft_putuns(l / 10, fd, count);
		ft_putchar((l % 10) + 48, fd, count);
	}
	else
		ft_putchar(l + 48, fd, count);
}