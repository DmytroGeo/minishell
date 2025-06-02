/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:03:41 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/31 17:03:53 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_array_free(char **array, size_t k)
{
	size_t	j;

	j = 0;
	if (!array)
		return (NULL);
	while (j < k)
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (NULL);
}
