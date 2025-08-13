/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:38:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/12 12:29:10 by dgeorgiy         ###   ########.fr       */
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
		if (!(ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1]))
				|| (str[i] == '+' && ft_isdigit(str[i + 1]))))
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

/**
 * @brief This function exits minishell, except in the case that
 * there is more than one argument and the first arguments is numeric.
 * We exit with a default exit code of 0. In case of a non-numeric argument,
 * it exits with an exit code of 2. However, if exit has exactly one argument,
 * and that argument is a number, it exits with that error code.
 * @param args the arguments of exit
 * @param cshell The main 'cshell' structure.
 * @return void - returns nothing.
 */
void	ft_exit(char **args, t_cshell *cshell)
{
	int	i;

	i = -1;
	if (args[0])
		i = ft_contains_only_digit(args[0]);
	else
		cshell->exit_code = 0;
	if (i == 0)
	{
		ft_printf(2, "exit: %s:", args[0]);
		ft_printf(2, "numeric argument required\n");
		cshell->exit_code = 2;
	}
	if (i == 1 && ft_array_len(args) > 1)
	{
		ft_printf(2, "exit\nminishell: exit: too many arguments\n");
		cshell->exit_code = 1;
		return ;
	}
	if (ft_array_len(args) == 1 && i != 0)
		cshell->exit_code = correct_integer(ft_atoi(args[0]));
	free_whole_cshell(cshell);
	ft_printf(1, "exit\n");
	exit(cshell->exit_code);
}
