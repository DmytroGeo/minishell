/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:13:51 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:18:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	// Arguments: const char *s – the string to search, int c – the character to find (as an integer).
	// Returns: A pointer to the first occurrence of the character 'c' in the string 's', or NULL if 'c' is not found.
	// This function searches for the first occurrence of the character 'c' in the string 's'. If 'c' is the null terminator ('\0'), it returns a pointer to the end of the string.
	size_t			n;
	unsigned char	uc;
	char			*str;

	str = (char *)s;
	n = 0;
	uc = (unsigned char)c;
	if (uc == '\0')
		return (str + ft_strlen(str));
	else
	{
		while (str[n] != '\0')
		{
			if (str[n] == uc)
				return (str + n);
			n++;
		}
		return (NULL);
	}
}
