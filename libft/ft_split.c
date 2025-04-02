/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:59:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:17:18 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ptrnbr(char const *s, char c)
{
	// Arguments: char const *s – the string to search, char c – the character to look for as the delimiter.
	// Returns: The number of substrings separated by the character 'c' in the string 's'.
	// This function counts how many substrings exist in the string 's' that are delimited by the character 'c'.
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[n])
	{
		if (s[n] != c)
		{
			i++;
			while (s[n] != c && s[n] != '\0')
				n++;
		}
		if (s[n] != '\0')
			n++;
	}
	return (i);
}

char	*ft_malloccpy(size_t n, size_t len, char const *s)
{
	// Arguments: size_t n – starting index of the substring, size_t len – length of the substring, char const *s – the string to copy from.
	// Returns: A new dynamically allocated string that is a copy of the substring starting at index 'n' with length 'len', or NULL if memory allocation fails.
	// This function allocates memory for a new string, copies the substring from 's' starting at index 'n' for 'len' characters, and null-terminates the string.
	char	*ptr;

	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, &s[n - len], len);
	ptr[len] = '\0';
	return (ptr);
}

char	**ft_free(char **ptr, size_t k)
{
	// Arguments: char **ptr – the array of strings to free, size_t k – the number of strings in the array.
	// Returns: NULL, freeing the allocated memory for the array and its contents.
	// This function frees each string in the array 'ptr' up to index 'k', then frees the array itself, and returns NULL.
	size_t	j;

	j = 0;
	while (j < k)
	{
		free(ptr[j]);
		j++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_arrayfill(char **array, char const *s, char c)
{
	// Arguments: char **array – the array to fill with substrings, char const *s – the string to split, char c – the delimiter character.
	// Returns: The filled array of strings or NULL if memory allocation fails.
	// This function fills the array 'array' with substrings from the string 's', splitting by the delimiter 'c', allocating memory for each substring.
	size_t	n;
	size_t	k;
	size_t	len;

	n = 0;
	k = 0;
	len = 0;
	while (s[n])
	{
		if (s[n] != c)
		{
			while (s[n + len] != c && s[n + len] != '\0')
				len++;
			array[k] = ft_malloccpy(n + len, len, s);
			if (array[k] == NULL)
				return (ft_free(array, k));
			k++;
			n = n + len;
			len = 0;
		}
		if (s[n])
			n++;
	}
	array[k] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	// Arguments: char const *s – the string to split, char c – the delimiter character.
	// Returns: A dynamically allocated array of strings, or NULL if memory allocation fails.
	// This function splits the string 's' into substrings based on the delimiter 'c' and returns an array of those substrings.
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((ft_ptrnbr(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	return (ft_arrayfill(array, s, c));
}
