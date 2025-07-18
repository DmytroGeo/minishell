/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:07:44 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 10:51:08 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			k;
	unsigned char	*st1;
	unsigned char	*st2;

	k = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while (k < n)
	{
		if (st1[k] > st2[k])
			return (1);
		else if (st1[k] < st2[k])
			return (-1);
		k++;
	}
	return (0);
}
