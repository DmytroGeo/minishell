/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:57:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/12 17:34:43 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exist_err(char *file_name)
{
	ft_printf(2, "minishell: %s: No such file or directory\n", file_name);
}

void	perm_error(char *file_name)
{
	ft_printf(2, "minishell: %s: Permission denied\n", file_name);
}
