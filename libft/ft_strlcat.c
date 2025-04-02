/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:56:45 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:20:52 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	// Arguments: char *dst – the destination string to which 'src' will be appended, const char *src – the string to append to 'dst', size_t size – the size of the destination buffer.
	// Returns: The total length of the string it tried to create (i.e., the initial length of 'dst' plus the length of 'src'), or the sum of 'size' and the length of 'src' if 'size' is less than or equal to the length of 'dst'.
	// This function appends 'src' to 'dst' while ensuring that 'dst' does not exceed the given 'size'. It also ensures that the result is null-terminated.
	size_t	slen;
	size_t	dlen;
	size_t	n;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	n = 0;
	if (size > dlen)
	{
		while (n < size - dlen - 1 && src[n])
		{
			dst[n + dlen] = src[n];
			n++;
		}
		dst[n + dlen] = '\0';
		return (dlen + slen);
	}
	return (size + slen);
}
