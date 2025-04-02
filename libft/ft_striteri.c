/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:01:45 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:19:31 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	// Arguments: char *s – the string to iterate over, void (*f)(unsigned int, char*) – the function to apply to each character.
	// Returns: Nothing (void function).
	// This function applies the function 'f' to each character in the string 's', passing the index of the character and a pointer to the character itself.
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(s);
	i = 0;
	while (i != len)
	{
		(f)(i, &s[i]);
		i++;
	}
}
