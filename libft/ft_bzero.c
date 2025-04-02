/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:36:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 14:55:24 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	// Arguments: void *s – a pointer to the memory block to be cleared, size_t n – the number of bytes to set to zero.
	// Returns: Nothing (void function).
	// This function sets the first 'n' bytes of the memory area pointed to by 's' to zero, effectively "zeroing out" the specified memory region.
	unsigned char	*str;

	str = s;
	while (n != 0)
	{
		n--;
		str[n] = 0;
	}
}
