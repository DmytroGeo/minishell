/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:15:59 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 11:20:55 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (EXIT_FAILURE);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(int fd, char **arguments)
{
	int	has_flag;
	int	number_of_arguments;
	int	i;

	i = 0;
	has_flag = 0;
	if (arguments[i] && is_echo_flag(arguments[i]) == EXIT_SUCCESS)
	{
		has_flag = 1;
		while (arguments[i] && is_echo_flag(arguments[i]) == EXIT_SUCCESS)
			i++;
	}
	number_of_arguments = ft_array_len(arguments + i);
	while (i < number_of_arguments - 1)
	{
		ft_printf(fd, "%s ", arguments[i]);
		i++;
	}
	ft_printf(fd, "%s", arguments[i]);
	if (has_flag == 0)
		ft_printf(fd, "\n");
	return (0);
}
