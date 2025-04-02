/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:35:42 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:20:18 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	// Arguments: char const *s1 – the first string, char const *s2 – the second string to join with the first.
	// Returns: A new string that is the concatenation of 's1' and 's2', or NULL if memory allocation fails.
	// This function allocates memory for a new string that combines 's1' and 's2', copies the contents of both strings into the new string, and null-terminates it.
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}
