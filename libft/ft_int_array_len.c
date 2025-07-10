/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_array_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:26:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/07 15:40:31 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_array_len(int **array)
{
	int	n;

	n = 0;
	if (!array)
		return (n);
	while (array[n] != NULL)
		n++;
	return (n);
}