/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:46:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 19:48:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * @brief This function prints the current working directory.
 * @param outfile_fd the file descriptor to write to.
 * @return void - returns nothing.
 */
void	ft_pwd(int outfile_fd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_printf(outfile_fd, "%s\n", cwd);
	free(cwd);
	return ;
}
