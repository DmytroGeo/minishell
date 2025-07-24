/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:38:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/24 12:47:56 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_contains_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1]))))
			return (0);
		i++;
	}
	return (1);
}

int	correct_integer(int n)
{
	int	i;

	i = n % 256;
	if (i < 0)
		i += 256;
	return (i);
}

void	exit_err1(char *str)
{
	ft_printf(2, "exit: %s: numeric argument required\n", str);
}

int	ft_exit(char **cmd_and_args, t_cshell *cshell)
{
	int	exit_code;

	exit_code = 0;
	if (ft_array_len(cmd_and_args) > 2)
		return (ft_printf(2, "exit\nminishell: exit: too many arguments"), 1);
	if (ft_array_len(cmd_and_args) == 2)
	{
		if (ft_contains_only_digit(cmd_and_args[1]))
			exit_code = correct_integer(ft_atoi(cmd_and_args[1]));
		else
		{
			exit_err1(cmd_and_args[1]);
			exit_code = 2;
		}
	}
	free_whole_cshell(cshell);
	ft_printf(1, "exit\n");
	exit(exit_code);
}
