/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:27:11 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:09:51 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	// Arguments: void *dest – pointer to the destination memory block, const void *src – pointer to the source memory block, size_t n – number of bytes to move.
	// Returns: A pointer to the destination memory block 'dest'.
	// This function moves 'n' bytes from the source memory block 'src' to the destination memory block 'dest'. It handles overlapping regions by copying from the beginning if 'src' is greater than or equal to 'dest', or from the end if 'src' is less than 'dest'.
	unsigned char		*d;
	unsigned const char	*s;
	size_t				k;

	k = 0;
	s = src;
	d = dest;
	if (src >= dest)
	{
		while (k < n)
		{
			d[k] = s[k];
			k++;
		}
	}
	else if (src < dest)
	{
		while (n != 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}
