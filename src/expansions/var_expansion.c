/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:07:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/06 17:28:02 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

int	expand_code(t_exp *exp, t_cshell *cshell)
{
	if (*(exp->exp_start) == '$')
		exp->exp_str = ft_itoa(cshell->shell_id);
	else
		exp->exp_str = ft_itoa(cshell->exec_code);
	if (!exp->exp_str)
		return (free_exp(exp), -42);
	exp->exp_strlen = ft_strlen(exp->exp_str);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!exp->str)
		return (free_exp(exp), -42);
	free(exp->temp);
	free(exp->exp_str);
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->exp_start = &((exp->str)[ft_strlen(exp->str) - 1]);
	exp->exp_end = exp->exp_start;
	exp->strlen += exp->exp_strlen;
	exp->i += 2;
	return (0);
}

int	expand_variable(t_exp *exp, t_cshell *cshell)
{
	if (find_exp_var(exp, cshell->envp) < 0)
		return (free_exp(exp), -42);
	if (exp->exp_var)
	{
		exp->exp_varlen = ft_strlen(exp->exp_var);
		exp->temp = exp->str;
		exp->str = ft_strjoin(exp->temp, exp->exp_var);
		if (!(exp->str))
			return (free_exp(exp), -42);
		free(exp->temp);
		free(exp->exp_var);
		exp->temp = NULL;
		exp->exp_var = NULL;
		exp->strlen += exp->exp_varlen;
		exp->exp_end = &((exp->str)[exp->strlen - 1]);
		exp->exp_start = exp->exp_end - exp->exp_varlen;
	}
	exp->i += exp->varlen + 1;
	return (0);
}

int	check_and_expand_var(t_exp *exp, t_cshell *cshell)
{
	if (!*(exp->exp_start))
		return (add_one_char_to_string(exp, '$'));
	else
	{
		if (*(exp->exp_start) == '$' || *(exp->exp_start) == '?')
			return (expand_code(exp, cshell));
		else if (*(exp->exp_start) == '\'' || *(exp->exp_start) == '"')
		{
			exp->i++;
			exp->exp_end = exp->exp_start;
		}
		else
		{
			exp->varlen = find_varlen(exp->exp_start);
			if (exp->varlen == 0)
			{
				exp->i++;
				exp->exp_end = exp->exp_start;
			}
			else
				return (expand_variable(exp, cshell));
		}
	}
	return (0);
}
