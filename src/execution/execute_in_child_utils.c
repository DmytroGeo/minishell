/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:14:44 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/19 19:27:55 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	exit_with_code(t_cshell *cshell, int i)
{
	cshell->exit_code = i;
	(free_whole_cshell(cshell), exit(cshell->exit_code));
}

int	is_directory(char *str)
{
	struct stat	st;

	if (access(str, F_OK) != 0)
		return (false);
	stat(str, &st);
	return (S_ISDIR(st.st_mode));
}

void	exec_err_1(char *str)
{
	ft_printf(2, "minishell: ");
	ft_printf(2, "%s: Is a directory\n", str);
}

void	exec_err_2(char *str)
{
	ft_printf(2, "minishell: ");
	ft_printf(2, "%s: error executing\n", str);
}
