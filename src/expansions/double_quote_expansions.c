/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_expansions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:05:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/04 11:42:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

int	expand_code_in_dquotes(t_exp *exp, t_cshell *cshell)
{
	char	*code;
	int		len;

	if (*(exp->exp_start) == '$')
		code = ft_itoa(cshell->shell_id);
	else
		code = ft_itoa(cshell->exec_code);
	len = ft_strlen(code);
	if (!code)
		return (free_exp(exp), -42);
	exp->temp = exp->exp_str;
	exp->exp_str = ft_strjoin(exp->temp, code);
	if (!exp->str)
		return (free(code), free_exp(exp), -42);
	free(code);
	free(exp->temp);
	exp->temp = NULL;
	exp->exp_strlen += len;
	exp->exp_start += 1;
	return (0);
}

int expand_non_var(t_exp *exp)
{
	char	*non_var_str;
	int		non_var_strlen;
	
	non_var_strlen = exp->exp_end - exp->exp_start;
	if (non_var_strlen == 0)
		return (0);
	non_var_str = ft_calloc(non_var_strlen + 1, sizeof(char));
	if (!non_var_str)
		return (free_exp(exp), -42);
	non_var_str = ft_memcpy(non_var_str, exp->exp_start, non_var_strlen);
	exp->temp = exp->exp_str;
	exp->exp_str = ft_strjoin(exp->temp, non_var_str);
	if (!non_var_str)
		return (free_exp(exp), -42);
	exp->exp_strlen += non_var_strlen;
	exp->exp_start += non_var_strlen;
	return (0);	
}

int	check_and_expand_var_in_dquotes(t_exp *exp, t_cshell *cshell)
{
	exp->exp_start += 1;
	if (*(exp->exp_start) == '"')
		return (add_one_char_to_exp(exp, '$'));
	else
	{
		if (*(exp->exp_start) == '$' || *(exp->exp_start) == '?')
			return (expand_code_in_dquotes(exp, cshell));
		else
		{
			exp->varlen = find_varlen(exp->exp_start);
			if (exp->varlen == 0)
				add_one_char_to_exp(exp, *(exp->exp_start));
			else
				return (expand_var_in_dquotes(exp, cshell));
		}
	}
	return (0);
}

int add_everything_else_to_str(t_exp *exp)
{
	char	*dquote;
	int		len;
	char	*last_bit;

	exp->temp = exp->exp_str;
	dquote = ft_strchr(exp->exp_start, '"');
	len = exp->exp_strlen + dquote - exp->exp_start;
	last_bit = ft_calloc(len + 1, sizeof(char));
	last_bit = ft_memcpy(last_bit, exp->exp_start, dquote - exp->exp_start);
	exp->exp_str = ft_strjoin(exp->temp, last_bit);
	if (!(exp->exp_str))
		return (free_exp(exp), -42);
	exp->exp_strlen = ft_strlen(exp->exp_str);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!(exp->str))
		return (free_exp(exp), -42);
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->exp_strlen;
	return (0);	
}

int	expand_double_quotes(t_exp *exp, t_cshell *cshell)
{
	exp->i++;
	exp->exp_str = "";
	exp->exp_end = ft_dollar_strchr(exp->exp_start);
	while (exp->exp_end)
	{
		if (expand_non_var(exp) < 0)
			return (-42);
		if (check_and_expand_var_in_dquotes(exp, cshell) < 0)
			return (-42);
		exp->exp_end = ft_dollar_strchr(exp->exp_start);
	}
	if (add_everything_else_to_str(exp) < 0)
		return (-42);
	return (0);
}
