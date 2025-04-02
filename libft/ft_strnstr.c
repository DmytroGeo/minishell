/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:49:18 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:23:53 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	// Arguments: const char *big – the string to search in, const char *little – the substring to search for, size_t len – the maximum number of characters to search through.
	// Returns: A pointer to the first occurrence of 'little' in 'big' within the first 'len' characters, or NULL if 'little' is not found.
	// This function searches for the substring 'little' within 'big' up to 'len' characters, returning a pointer to the first match or NULL if no match is found.
	size_t	k;
	char	*b;
	char	*l;

	k = 0;
	b = (char *)big;
	l = (char *)little;
	if (!*b || !b)
	{
		if (!*l || !l)
			return (b);
		return (NULL);
	}
	else
	{
		while (len - k >= ft_strlen(l))
		{
			if (ft_strncmp(b + k, l, ft_strlen(l)) == 0)
				return (b + k);
			k++;
		}
	}
	return (NULL);
}
