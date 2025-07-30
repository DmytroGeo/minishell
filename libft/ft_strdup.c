/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:19:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/29 19:09:07 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief This function allocates memory for a new string
 * and copies the content of the string 's' into the newly allocated memory,
 *  including the null terminator.
 * @param s He string to duplicate.
 * @return A new string that is a copy of 's',
 *  or NULL if memory allocation fails.
 */
char	*ft_strdup(const char *s)
{
	char	*str;

	str = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (ft_strlen(s) == 0)
		return (str);
	else
		ft_memcpy(str, s, ft_strlen(s));
	return (str);
}
