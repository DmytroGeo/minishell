/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:27:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2024/11/26 15:22:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	// Arguments: char const *s – the string to iterate over, char (*f)(unsigned int, char) – the function to apply to each character along with its index.
	// Returns: A new string where each character is transformed by applying function 'f', or NULL if memory allocation fails.
	// This function allocates memory for a new string and applies the function 'f' to each character in the input string 's', using the character's index. The result is stored in a new string, which is null-terminated.
	unsigned int	i;
	unsigned int	len;
	char			*ptr;

	len = ft_strlen(s);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (i != len)
	{
		ptr[i] = (f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
