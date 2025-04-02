/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:19:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:18:37 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	// Arguments: const char *s – the string to duplicate.
	// Returns: A new string that is a copy of 's', or NULL if memory allocation fails.
	// This function allocates memory for a new string and copies the content of the string 's' into the newly allocated memory, including the null terminator.
	char	*str;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	else
		ft_memcpy(str, s, ft_strlen(s) + 1);
	return (str);
}
