/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:49:08 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 19:51:44 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * @brief This function prints those strings in (char **)(minishell->envp) that
 * have an '=' in them. So if we run the command 'export a=hello b', then 
 * run env, of the two, only a=hello will show up.
 * @param outfile_fd the file descriptor to write to.
 * @param envp our copy of envp.
 * @return void - returns nothing.
 */
void	print_envp(int outfile_fd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf(outfile_fd, "%s\n", envp[i]);
		i++;
	}
	return ;
}
