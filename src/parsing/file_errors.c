/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:57:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 21:29:35 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	existence_error(char *file_name)
{
	ft_printf(2, "minishell: %s: No such file or directory\n", file_name);
}

void	permission_error(char *file_name)
{
	ft_printf(2, "minishell: %s: Permission denied\n", file_name);
}
