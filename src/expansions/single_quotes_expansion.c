/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:03:42 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/11 10:54:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

int	expand_single_quotes(t_exp *exp)
{
	exp->exp_end = ft_strchr(exp->exp_start, '\'');
	exp->exp_strlen = exp->exp_end - exp->exp_start;
	exp->exp_str = ft_calloc(exp->exp_strlen + 1, sizeof(char));
	if (!(exp->exp_str))
		return (free_exp(exp), -42);
	exp->exp_str = ft_memcpy(exp->exp_str, exp->exp_start, exp->exp_strlen);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!(exp->exp_str))
		return (free_exp(exp), -42);
	(free(exp->temp), free(exp->exp_str));
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->exp_strlen;
	(exp->i) += exp->exp_strlen + 2;
	return (0);
}
