/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:09:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 10:14:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intconvert(const char *nptr)
{
	int		n;
	size_t	k;

	n = 0;
	k = 0;
	while (ft_isdigit(nptr[k]))
	{
		n = (10 * n) + (nptr[k] - 48);
		k++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int		n;

	n = 0;
	while (ft_isspace(nptr[n]))
		n++;
	if (nptr[n] == '-')
		return (-1 * ft_intconvert(nptr + n + 1));
	else if (nptr[n] == '+')
		n++;
	if (ft_isdigit(nptr[n]))
		return (ft_intconvert(nptr + n));
	return (0);
}
