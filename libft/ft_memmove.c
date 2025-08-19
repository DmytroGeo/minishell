/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:27:11 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:14:18 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				k;

	k = 0;
	s = src;
	d = dest;
	if (src >= dest)
	{
		while (k < n)
		{
			d[k] = s[k];
			k++;
		}
	}
	else if (src < dest)
	{
		while (n != 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}
