/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:07:44 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:23:16 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	// Arguments: const char *s1 – the first string, const char *s2 – the second string, size_t n – the number of characters to compare.
	// Returns: 0 if the first 'n' characters of both strings are equal, a positive value if 's1' is greater, or a negative value if 's2' is greater.
	// This function compares the first 'n' characters of two strings 's1' and 's2' lexicographically, returning the difference between the first differing characters or 0 if they are equal.
	size_t			k;
	unsigned char	*st1;
	unsigned char	*st2;

	k = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while (k < n)
	{
		if (st1[k] > st2[k])
			return (1);
		else if (st1[k] < st2[k])
			return (-1);
		k++;
	}
	return (0);
}
