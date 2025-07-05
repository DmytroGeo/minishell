/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:38:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:33:03 by dgeorgiy         ###   ########.fr       */
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

int	ft_exit(char **commands_and_arguments, int *pid, int **fd, t_simple_command *simple_command)
{
	int exit_code;
	
	exit_code = 0;
	if (ft_array_len(commands_and_arguments) > 1)
	{
		ft_printf(2, "exit: too many arguments");
		return (0);
	}
	if (ft_array_len(commands_and_arguments) == 1 && ft_contains_only_digit(commands_and_arguments[0]))
		exit_code = ft_atoi(commands_and_arguments[1]);
	ft_array_free(commands_and_arguments, ft_array_len(commands_and_arguments));
	if (pid && fd)
	{
		free(pid);
		ft_intarr_free(fd, ft_int_array_len(fd));
	}
	free_simple_command(simple_command);
	exit(exit_code);    
}
