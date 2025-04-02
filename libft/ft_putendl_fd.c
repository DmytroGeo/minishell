/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:42:05 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:11:41 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	// Arguments: char *s – the string to write, int fd – the file descriptor to write to.
	// Returns: Nothing (void function).
	// This function writes the string 's' followed by a newline character to the file descriptor 'fd'.
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
