/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:19:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:09:01 by dgeorgiy         ###   ########.fr       */
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

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	else
		ft_memcpy(str, s, ft_strlen(s) + 1);
	return (str);
}
