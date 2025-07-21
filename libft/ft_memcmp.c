/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:12:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:17:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*str1;
	unsigned const char	*str2;
	size_t				k;

	str1 = (unsigned const char *)s1;
	str2 = (unsigned const char *)s2;
	k = 0;
	while (k < n)
	{
		if (str1[k] != str2[k])
			return (str1[k] - str2[k]);
		k++;
	}
	return (0);
}
