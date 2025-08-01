/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:07:22 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/01 20:01:52 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

int	expand_code(t_exp *exp, t_cshell *cshell, t_token **head)
{
	if (*(exp->exp_start) == '$')
		exp->exp_str = ft_itoa(cshell->shell_id);
	else
		exp->exp_str = ft_itoa(cshell->exec_code);
	if (!exp->exp_str)
		return (free_exp(exp), free_tok_chain(head, del_tok_cont), -42);
	exp->exp_strlen = ft_strlen(exp->exp_str);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!exp->str)
		return (free_exp(exp), free_tok_chain(head, del_tok_cont), -42);
	free(exp->temp);
	free(exp->exp_str);
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->exp_strlen;
	exp->i += 2;
	return (0);
}

int	expand_variable(t_exp *exp, t_cshell *cshell, t_token **head)
{
	exp->exp_end = exp->exp_start + exp->exp_varlen;
	if (find_exp_var(exp, cshell->envp) < 0)
		return (free_exp(exp), free_tok_chain(head, del_tok_cont), -42);
	if (exp->exp_str)
	{
		exp->exp_strlen = ft_strlen(exp->exp_str);
		exp->temp = exp->str;
		exp->str = ft_strjoin(exp->temp, exp->exp_str);
		if (!(exp->str))
		{
			(free_exp(exp), free_tok_chain(head, del_tok_cont));
			return (-42);
		}
		free(exp->temp);
		free(exp->exp_str);
		exp->temp = NULL;
		exp->exp_str = NULL;
		exp->strlen += exp->exp_strlen;
	}
	exp->i += exp->varlen + 1;
	return (0);
}

int	check_and_expand_var(t_exp *exp, t_cshell *cshell, t_token **head)
{
	if (!*(exp->exp_start))
		return (add_one_char_to_string(exp, '$', head));
	else
	{
		if (*(exp->exp_start) == '$' || *(exp->exp_start) == '?')
			return (expand_code(exp, cshell, head));
		else if (*(exp->exp_start) == '\'' || *(exp->exp_start) == '"')
			exp->i++;
		else
		{
			exp->varlen = find_varlen(exp->exp_start);
			if (exp->varlen == 0)
				exp->i += 2;
			else
				return (expand_variable(exp, cshell, head));
		}
	}
	return (0);
}
