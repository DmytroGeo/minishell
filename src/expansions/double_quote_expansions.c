/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_expansions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:05:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/11 11:41:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

int	expand_non_var(t_exp *exp, char *next_dollar_sign)
{
	exp->varlen = next_dollar_sign - exp->exp_start;
	if (exp->varlen == 0)
		return (0);
	exp->exp_str = ft_calloc(exp->varlen + 1, sizeof(char));
	if (!(exp->exp_str))
		return (free_exp(exp), -42);
	exp->exp_str = ft_memcpy(exp->exp_str, exp->exp_start, exp->varlen);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!(exp->str))
		return (free_exp(exp), -42);
	(free(exp->temp), free(exp->exp_str));
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->varlen;
	exp->exp_start += exp->varlen;
	exp->i += exp->varlen;
	return (0);
}

int	check_and_expand_var_in_dquotes(t_exp *exp, t_cshell *cshell)
{
	int	return_code;

	exp->exp_start += 1;
	if (is_special_char(*(exp->exp_start)))
		return (add_one_char_to_string(exp, '$'));
	if (*(exp->exp_start) == '$' || *(exp->exp_start) == '?')
	{
		return_code = expand_code(exp, cshell);
		exp->exp_start++;
		return (return_code);
	}
	exp->varlen = find_varlen(exp->exp_start);
	if (exp->varlen != 0)
		return (expand_var_in_dquotes(exp, cshell));
	exp->i += 2;
	exp->exp_start++;
	return (0);
}

int	add_everything_else_to_str(t_exp *exp)
{
	exp->varlen = exp->exp_end - exp->exp_start;
	exp->exp_str = ft_calloc(exp->varlen + 1, sizeof(char));
	if (!(exp->exp_str))
		return (free_exp(exp), -42);
	exp->exp_str = ft_memcpy(exp->exp_str, exp->exp_start, exp->varlen);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!(exp->exp_str))
		return (free_exp(exp), -42);
	(free(exp->temp), free(exp->exp_str));
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->varlen;
	exp->i += exp->varlen + 1;
	exp->exp_start += exp->varlen + 1;
	return (0);
}

int	expand_double_quotes(t_exp *exp, t_cshell *cshell)
{
	char	*next_dollar_sign;

	exp->i++;
	exp->exp_end = ft_strchr(exp->exp_start, '"');
	if (exp->exp_start == exp->exp_end)
	{
		exp->exp_strlen = 0;
		exp->i += 1;
	}
	else
	{
		next_dollar_sign = ft_dollar_strchr(exp->exp_start);
		while (next_dollar_sign)
		{
			if (expand_non_var(exp, next_dollar_sign) < 0)
				return (-42);
			if (check_and_expand_var_in_dquotes(exp, cshell) < 0)
				return (-42);
			next_dollar_sign = ft_dollar_strchr(exp->exp_start);
		}
		if (add_everything_else_to_str(exp) < 0)
			return (-42);
	}
	return (0);
}
