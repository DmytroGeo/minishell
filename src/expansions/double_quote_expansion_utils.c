/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_expansion_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:51:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/04 11:42:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_dollar_strchr(const char *s)
{
	size_t	n;
	char	*str;

	str = (char *)s;
	n = 0;
	while (str[n] != '\0' && str[n] != '"')
	{
		if (str[n] == '$')
			return (str + n);
		n++;
	}
	return (NULL);
}

int	add_one_char_to_exp(t_exp *exp, char c)
{
	exp->temp = exp->exp_str;
	exp->exp_str = ft_calloc(exp->exp_strlen + 2, sizeof(char));
	if (!(exp->exp_str))
		return (free_exp(exp), -42);
	exp->exp_str = ft_memcpy(exp->exp_str, exp->temp, exp->exp_strlen);
	(exp->exp_str)[exp->exp_strlen] = c;
	free(exp->temp);
	exp->temp = NULL;
	(exp->exp_strlen)++;
	(exp->exp_start)++;
	return (0);
}
