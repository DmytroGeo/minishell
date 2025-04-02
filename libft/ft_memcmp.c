/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:12:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:08:17 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	// Arguments: const void *s1 – pointer to the first memory block, const void *s2 – pointer to the second memory block, size_t n – the number of bytes to compare.
	// Returns: 0 if the memory blocks are identical, a negative value if 's1' is less than 's2', or a positive value if 's1' is greater than 's2'.
	// This function compares the first 'n' bytes of the memory blocks 's1' and 's2'. It returns the difference between the first pair of unequal bytes, or 0 if the blocks are equal.
	unsigned const char	*str1;
	unsigned const char	*str2;
	size_t				k;

	str1 = (unsigned const char *)s1;
	str2 = (unsigned const char *)s2;
	k = 0;
	while (k < n)
	{
		if (str1[k] != str2[k])
			return (str1[k] - str2[k]);
		k++;
	}
	return (0);
}
