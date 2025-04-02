/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:29:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:12:52 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	// Arguments: char *s – the string to write, int fd – the file descriptor to write to.
	// Returns: Nothing (void function).
	// This function writes the string 's' to the file descriptor 'fd' by writing each character individually using ft_putchar_fd.
	size_t	n;

	n = 0;
	while (s[n])
	{
		ft_putchar_fd(s[n], fd);
		n++;
	}
}
