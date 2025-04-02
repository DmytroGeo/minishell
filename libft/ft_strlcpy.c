/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:40:05 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:21:22 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	// Arguments: char *dst – the destination string where 'src' will be copied, const char *src – the string to copy, size_t size – the size of the destination buffer.
	// Returns: The total length of the string 'src' (not the number of characters copied).
	// This function copies up to 'size - 1' characters from 'src' to 'dst' and ensures that 'dst' is null-terminated. It also returns the length of 'src'.
	size_t	n;

	n = 0;
	if (size >= 1)
	{
		while (n < size - 1 && src[n])
		{
			dst[n] = src[n];
			n++;
		}
		dst[n] = '\0';
	}
	return (ft_strlen(src));
}
