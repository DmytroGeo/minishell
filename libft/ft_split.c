/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:59:24 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 15:37:25 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ptrnbr(char const *s, char c)
{
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
	char	*ptr;

	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, &s[n - len], len);
	ptr[len] = '\0';
	return (ptr);
}

char	**ft_arrayfill(char **array, char const *s, char c)
{
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
				return (ft_array_free((void **)array, k), NULL);
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
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((ft_ptrnbr(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	return (ft_arrayfill(array, s, c));
}
