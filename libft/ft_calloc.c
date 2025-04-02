/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:34:38 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 14:56:22 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	// Arguments: size_t nmemb – the number of elements, size_t size – the size of each element.
	// Returns: A pointer to the allocated memory, or NULL if the allocation fails.
	// This function allocates memory for an array of 'nmemb' elements, each of size 'size', initializes the memory to zero using 'ft_bzero', and returns a pointer to the allocated memory, or NULL if the allocation fails or the multiplication overflows.
	void	*ptr;

	if (size != 0 && ((SIZE_MAX) / size) < nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
