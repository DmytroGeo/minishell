/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:43:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:24:33 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	// Arguments: const char *s – the string to search in, int c – the character to search for.
	// Returns: A pointer to the last occurrence of 'c' in 's', or NULL if 'c' is not found.
	// This function searches for the last occurrence of character 'c' in the string 's'. If 'c' is the null character ('\0'), it returns a pointer to the end of the string.
	char			*str;
	unsigned char	uc;
	int				n;

	str = (char *)s;
	uc = (unsigned char)c;
	n = ft_strlen(str) - 1;
	if (uc == '\0')
		return (str + n + 1);
	else
	{
		while (n != -1)
		{
			if (str[n] == uc)
				return (str + n);
			n--;
		}
		return (NULL);
	}
}
