/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:15:19 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 13:16:00 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	infile_err1(char *str)
{
	ft_printf(2, "minishell: syntax error near unexpected token '%s'\n", str);
	return ; 
}

void	infile_err2(char *str)
{
	ft_printf(2, "minishell: %s: No such file or directory\n", str);
	return ;	
}

void	infile_err3(char *str)
{
	ft_printf(2, "minishell: %s: Permission denied\n", str);
	return ;
}