/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:23:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/15 15:34:49 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_array_len(char **array)
{
	int	n;

	n = 0;
	if (!array)
		return (n);
	while (array[n] != NULL)
		n++;
	return (n);
}
