/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:55:26 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:16:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	else if (n > 0 && n <= INT_MAX)
	{
		while (n != 0)
		{
			n = n / 10;
			len++;
		}
	}
	else if (n < 0 && n > INT_MIN)
		return (ft_nbrlen((-1) * n));
	else if (n == INT_MIN)
		return (10);
	return (len);
}

char	*ft_charconvert(char *ptr, unsigned int i, size_t sign, size_t len)
{
	ptr[len + sign] = '\0';
	while (len != 0)
	{
		len--;
		ptr[len + sign] = (i % 10) + 48;
		i = i / 10;
	}
	if (sign == 1)
		ptr[0] = '-';
	return (ptr);
}

size_t	ft_sign(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	size_t			len;
	size_t			sign;
	unsigned int	i;

	i = 0;
	sign = ft_sign(n);
	len = ft_nbrlen(n);
	ptr = malloc((len + 1 + sign) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (n >= 0)
		i = (unsigned int)n;
	else if (n < 0 && n > INT_MIN)
		i = (unsigned int)((-1) * n);
	else if (n == INT_MIN)
		i = (unsigned int)(INT_MAX) + 1;
	return (ft_charconvert(ptr, i, sign, len));
}
