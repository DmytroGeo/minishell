/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:56:45 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 10:55:33 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	dlen;
	size_t	n;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	n = 0;
	if (size > dlen)
	{
		while (n < size - dlen - 1 && src[n])
		{
			dst[n + dlen] = src[n];
			n++;
		}
		dst[n + dlen] = '\0';
		return (dlen + slen);
	}
	return (size + slen);
}
