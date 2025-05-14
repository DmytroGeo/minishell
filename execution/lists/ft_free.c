/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:22:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:25 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

char	**ft_free(char **ptr, size_t k)
{
	size_t	j;

	j = 0;
	while (j < k)
	{
		free(ptr[j]);
		j++;
	}
	free(ptr);
	return (NULL);
}
