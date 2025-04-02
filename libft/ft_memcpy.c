/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:50:57 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:09:07 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	// Arguments: void *dest – pointer to the destination memory block, const void *src – pointer to the source memory block, size_t n – number of bytes to copy.
	// Returns: A pointer to the destination memory block 'dest'.
	// This function copies the first 'n' bytes from the source memory block 'src' to the destination memory block 'dest', and returns the destination pointer.
	unsigned char		*d;
	unsigned const char	*s;

	d = dest;
	s = src;
	while (n != 0)
	{
		n--;
		d[n] = s[n];
	}
	return (dest);
}
