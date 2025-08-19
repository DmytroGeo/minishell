/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:03:41 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 11:32:22 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_array_free2(void **array, size_t k)
{
	size_t	j;

	j = 0;
	if (!array)
		return ;
	while (j < k)
	{
		free(array[j]);
		j++;
	}
	free(array);
	return ;
}
