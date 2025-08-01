/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_expansion_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:51:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/01 20:16:51 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_dquote_strchr(const char *s)
{
	size_t	n;
	char	*str;

	str = (char *)s;
	n = 0;
	while (str[n] != '\0' && str[n] != '"')
	{
		if (str[n] == '$')
			return (str + n);
		n++;
	}
	return (NULL);
}
