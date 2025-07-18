/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:13:51 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:09:23 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			n;
	unsigned char	uc;
	char			*str;

	str = (char *)s;
	n = 0;
	uc = (unsigned char)c;
	if (uc == '\0')
		return (str + ft_strlen(str));
	else
	{
		while (str[n] != '\0')
		{
			if (str[n] == uc)
				return (str + n);
			n++;
		}
		return (NULL);
	}
}
