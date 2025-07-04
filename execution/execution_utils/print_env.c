/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:49:08 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 09:49:58 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void print_env(int fd, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		ft_printf(fd, "%s\n", envp[i++]);
}