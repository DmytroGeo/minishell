/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:29:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:52 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_putstr_fd(char *s, int fd, int *count)
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
		ft_putchar_fd(s[n], fd, count);
		n++;
	}
}
