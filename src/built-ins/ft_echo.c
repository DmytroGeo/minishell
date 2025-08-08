/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:15:59 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 19:35:02 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

/**
 * @brief This function writes the strings **arguments to the outfile fd.
 * If we give echo the -n flag, or any flag which consists only of the letter
 * n (like -nnnnn) or any number of those flags (like echo -n -n hello),
 * it will not print a newline after it prints the arguments.
 * @param outfile_fd the file descriptor of the last valid outfile.
 * @param arguments the array of strings to write to outfile_fd.
 * @param cshell The main 'cshell' structure.
 * @return void - returns nothing.
 */
void	ft_echo(int outfile_fd, char **arguments, t_cshell *cshell)
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
	number_of_arguments = ft_array_len(arguments);
	while (i < number_of_arguments - 1)
	{
		ft_printf(outfile_fd, "%s ", arguments[i]);
		i++;
	}
	if (arguments[i])
		ft_printf(outfile_fd, "%s", arguments[i]);
	if (has_flag == 0)
		ft_printf(outfile_fd, "\n");
	cshell->exit_code = 0;
}
