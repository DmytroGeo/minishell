/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:40:05 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 10:54:58 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	if (size >= 1)
	{
		while (n < size - 1 && src[n])
		{
			dst[n] = src[n];
			n++;
		}
		dst[n] = '\0';
	}
	return (ft_strlen(src));
}
