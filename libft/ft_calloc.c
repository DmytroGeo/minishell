/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:34:38 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 11:15:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief a useful altrnative to malloc, especially for pointer arrays.
 * @return A malloc'd array where the entries have been initialised to 0.
 * In case of pointer array allocation, the pointers are initialised to NULL.
 * @param nmemb the number of structs
 * @param size the struct size
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && ((SIZE_MAX) / size) < nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
