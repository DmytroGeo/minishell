/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:26:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:26:05 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_forwardloop(char const *s1, char const *set)
{
	// Arguments: const char *s1 – the string to check, const char *set – the set of characters to remove from the start.
	// Returns: The number of characters from the start of 's1' that are found in 'set'.
	// This function counts how many characters from the beginning of 's1' belong to the set 'set' and returns that count.
	size_t	n;
	size_t	k;

	n = 0;
	k = 0;
	while (set[k] && s1[n])
	{
		if (set[k] == s1[n])
		{
			n++;
			k = 0;
		}
		else if (set[k] != s1[n])
			k++;
	}
	return (n);
}

size_t	ft_backwardloop(char const *s1, char const *set)
{
	// Arguments: const char *s1 – the string to check, const char *set – the set of characters to remove from the end.
	// Returns: The index of the last character in 's1' that is not in 'set'.
	// This function counts how many characters from the end of 's1' belong to the set 'set', returning the index of the last character left.
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] && i != 0)
	{
		if (set[j] == s1[i])
		{
			i--;
			j = 0;
		}
		else if (set[j] != s1[i])
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	// Arguments: const char *s1 – the string to trim, const char *set – the set of characters to remove from both ends of 's1'.
	// Returns: A new string with characters from 'set' removed from both ends of 's1', or an empty string if all characters are trimmed.
	// This function removes any characters in 'set' from the start and end of 's1', returning a newly allocated string containing the trimmed result.
	char	*ptr;
	size_t	x;
	size_t	y;

	x = ft_backwardloop(s1, set);
	y = ft_forwardloop(s1, set);
	if (y > x)
		return (ft_strdup(""));
	ptr = (char *)malloc((x - y + 2) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr = ft_memcpy(ptr, s1 + y, x - y + 1);
	ptr[x - y + 1] = '\0';
	return (ptr);
}
