/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:42:03 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/23 12:49:15 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_valid_without_equals(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
	}
	return (true);
}

int	is_valid_with_equals(char *str, char *equal_sign)
{
	int	i;

	i = 0;
	if (equal_sign == str || equal_sign[-1] == ' ' || equal_sign[1] == ' ')
		return (false);
	while (&str[++i] < equal_sign)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (false);
	}
	return (true);
}

int	is_valid_variable_assignment(char *str)
{
	char	*equal_sign;

	if (!str)
		return (false);
	equal_sign = ft_strchr(str, '=');
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	if (equal_sign)
		return (is_valid_with_equals(str, equal_sign));
	return (is_valid_without_equals(str));
}

int	is_valid_var_unset(char *str)
{
	char	*equal_sign;

	if (!str)
		return (false);
	equal_sign = ft_strchr(str, '=');
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	if (equal_sign)
		return (false);
	return (is_valid_without_equals(str));
}
