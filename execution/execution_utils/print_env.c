/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:49:08 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 16:43:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int print_env(int fd, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		ft_printf(fd, "%s\n", envp[i++]);
	return (0);
}