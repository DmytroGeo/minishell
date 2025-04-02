/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:19:10 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:11:02 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	// Arguments: char c – the character to write, int fd – the file descriptor to write to.
	// Returns: Nothing (void function).
	// This function writes the character 'c' to the file descriptor 'fd' using the write system call.
	write(fd, &c, 1);
}
