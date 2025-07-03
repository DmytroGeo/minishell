/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:15:59 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 09:52:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int		is_echo_flag(char *str)
{
	int i = 0;
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

void	ft_echo(int fd, char **arguments)
{
	char *big_string;
	int has_flag = 0;
	int number_of_arguments;
	int i = 0;
	char *temp;
	char *previous_big_string;
	if (arguments[i] && is_echo_flag(arguments[i]) == EXIT_SUCCESS)
	{
		has_flag = 1;
		while (arguments[i] && is_echo_flag(arguments[i]) == EXIT_SUCCESS)
			i++;		
	}
	number_of_arguments = ft_array_len(arguments + i);
	if (number_of_arguments == 1)
	{
		ft_printf(fd, "%s", arguments[i]);		
	}
	else if (number_of_arguments > 1)
	{
		previous_big_string = ft_strjoin(arguments[i], " ");
		i++;
		while (i < number_of_arguments - 1)
		{
			temp = ft_strjoin(arguments[i], " ");
			big_string = ft_strjoin(previous_big_string, temp);
			free(temp);
			free(previous_big_string);
			previous_big_string = big_string;
			i++;
		}
		big_string = ft_strjoin(previous_big_string, arguments[i]);	
		free(previous_big_string);
		ft_printf(fd, "%s", big_string);
	}
	if (has_flag == 0)
		ft_printf(fd, "\n", big_string);		
	return;
}