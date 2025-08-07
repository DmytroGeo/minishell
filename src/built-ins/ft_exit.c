/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:38:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/07 18:23:57 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
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

void	ft_exit(char **cmd_and_args, t_cshell *cshell)
{
	int	i;

	i = -1;
	if (cmd_and_args[1])
		i = ft_contains_only_digit(cmd_and_args[1]);
	else
		cshell->exec_code = 0;
	if (i == 0)
	{
		exit_err1(cmd_and_args[1]);
		cshell->exec_code = 2;
	}
	if (i == 1 && ft_array_len(cmd_and_args) > 2)
	{
		ft_printf(2, "exit\nminishell: exit: too many arguments\n");
		cshell->exec_code = 1;
		return ;
	}
	if (ft_array_len(cmd_and_args) == 2)
		cshell->exec_code = correct_integer(ft_atoi(cmd_and_args[1]));
	free_whole_cshell(cshell);
	ft_printf(1, "exit\n");
	exit(cshell->exec_code);
}
