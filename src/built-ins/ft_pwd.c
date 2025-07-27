/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:46:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:09:50 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_pwd(int outfile_fd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_printf(outfile_fd, "%s\n", cwd);
	free(cwd);
	return ;
}
