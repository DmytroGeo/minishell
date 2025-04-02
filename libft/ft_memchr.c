/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:07:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:07:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	// Arguments: const void *s – a pointer to the memory block to search, int c – the byte value to find, size_t n – the number of bytes to search.
	// Returns: A pointer to the first occurrence of the byte value 'c' in the memory block, or NULL if not found.
	// This function searches the first 'n' bytes of the memory block pointed to by 's' for the byte value 'c' and returns a pointer to its first occurrence, or NULL if 'c' is not found.
	size_t			k;
	unsigned char	uc;
	unsigned char	*str;

	k = 0;
	str = (unsigned char *)s;
	uc = (unsigned char)c;
	while (k < n)
	{
		if (str[k] == uc)
			return (str + k);
		k++;
	}
	return (NULL);
}
