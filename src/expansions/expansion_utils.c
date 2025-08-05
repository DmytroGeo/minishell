/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:51:26 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/02 12:03:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

void	free_exp(t_exp *exp)
{
	free(exp->str);
	exp->exp_str = NULL;
	free(exp->temp);
	exp->temp = NULL;
	free(exp->exp_str);
	exp->exp_str = NULL;
}

int	init_exp(t_exp *exp, char *value)
{
	exp->strlen = 1;
	exp->i = 0;
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->exp_start = NULL;
	exp->exp_end = NULL;
	exp->str = ft_calloc(exp->strlen, sizeof(char));
	if (!(exp->str))
		return (-42);
	return (0);
}

int	add_one_char_to_string(t_exp *exp, char c)
{
	exp->temp = exp->str;
	exp->str = ft_calloc(exp->strlen + 2, sizeof(char));
	if (!(exp->str))
		return (free_exp(exp), -42);
	exp->str = ft_memcpy(exp->str, exp->temp, exp->strlen);
	(exp->str)[exp->strlen] = c;
	free(exp->temp);
	exp->temp = NULL;
	(exp->strlen)++;
	(exp->i)++;
	return (0);
}
