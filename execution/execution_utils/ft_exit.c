/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:38:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/07 15:29:22 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_contains_only_digit(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1]))))
			return (0);
		i++;
	}
	return (1);
}

int correct_integer(int n)
{
	int i;
	
	i = n % 256;
	if (i < 0)
		i += 256;
	return (i);
}

int	ft_exit(char **command_and_arguments, int *pid, int **fd, t_simple_command *simple_command)
{
	int exit_code;
	
	exit_code = 0;
	if (ft_array_len(command_and_arguments) > 2)
	{
		ft_printf(2, "exit: too many arguments");
		return (0);
	}
	if (ft_array_len(command_and_arguments) == 2)
	{
		if (ft_contains_only_digit(command_and_arguments[1]))
			exit_code = correct_integer(ft_atoi(command_and_arguments[1])); // converts exit codes to those in range 0 to 255
		else
			ft_printf(2, "exit: %s: numeric argument required\n", command_and_arguments[1]);		
	}
	ft_array_free(command_and_arguments, ft_array_len(command_and_arguments));
	if (pid && fd)
	{
		free(pid);
		ft_intarr_free(fd, ft_int_array_len(fd));
	}
	free_simple_command(simple_command);
	ft_printf(1, "exit\n");
	exit(exit_code);    
}
