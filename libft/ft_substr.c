/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:37:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 10:38:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_min(size_t a, int b)
{
	if ((int)a > b && b >= 0)
		return (b);
	else
		return (a);
}

size_t	ft_msize(size_t c, int d)
{
	if (d < 0)
		return (1);
	return (c);
}

/**
 * @brief Extracts a substring from the given string 's'.
 * @param s The source string to extract the substring from.
 * @param start The starting index in 's' where the substring begins.
 * @param len The maximum length of the substring.
 * @return Returns a new string containing the substring,
 *  or NULL if memory allocation fails.
 * If 'start' exceeds the length of 's', returns an empty string.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;
	size_t	min;

	n = 0;
	min = ft_min(len, ft_strlen(s) - start);
	str = malloc(ft_msize(min + 1, ft_strlen(s) - start) * sizeof(char));
	if (!str)
		return (NULL);
	if (ft_strlen(s) > start)
	{
		while (n < min)
		{
			str[n] = s[start + n];
			n++;
		}
		str[n] = '\0';
	}
	else
		ft_bzero(str, 1);
	return (str);
}
