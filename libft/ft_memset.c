/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:45:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:10:23 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	// Arguments: void *s – pointer to the memory block to fill, int c – the byte value to set, size_t n – the number of bytes to set.
	// Returns: A pointer to the memory block 's'.
	// This function fills the first 'n' bytes of the memory block pointed to by 's' with the byte value 'c' and returns the pointer to the memory block.
	unsigned char	*str;

	str = s;
	while (n != 0)
	{
		n--;
		str[n] = c;
	}
	return (s);
}
