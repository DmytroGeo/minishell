/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:57:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 12:39:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	infile_err2(char *file_name)
{
	ft_printf(2, "minishell: %s: No such file or directory\n", file_name);
}

void	infile_err3(char *file_name)
{
	ft_printf(2, "minishell: %s: Permission denied\n", file_name);
}
