/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_expansions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:05:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/01 20:56:28 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

// char	*find_var(const char *var, int varlen)
// {
// 	char	*key;

// 	key = ft_calloc(varlen + 1, sizeof(char));
// 	if (!key)
// 		return (NULL);
// 	key = ft_memcpy(key, var, varlen);
// 	return (key);
// }

// void	strjoin_expanded_var(t_exp *exp, t_cshell *cshell)
// {next_dollar_sign - exp->exp_start
// 	char	*var;

// 	exp->varlen = find_varlen(exp->cur + 1);
// 	if (exp->varlen == 1 && *(exp->cur + 1) == '?')
// 		exp->expanded_var = ft_itoa(cshell->exec_code);
// 	else if (exp->varlen == 1 && *(exp->cur + 1) == '$')
// 		exp->expanded_var = ft_itoa(cshell->shell_id);
// 	else
// 	{
// 		var = find_var(exp->cur + 1, exp->varlen);
// 		if (!var)
// 			(free_exp(exp), free_whole_cshell(cshell), exit(-42));
// 		exp->expanded_var = ft_strdup(find_var_in_envp(cshell->envp, var));
// 		free(var);
// 	}
// 	if (!(exp->expanded_string))
// 		(free_exp(exp), free_whole_cshell(cshell), exit(-42));
// 	exp->temp = exp->expanded_string;
// 	exp->expanded_string = ft_strjoin(exp->temp, exp->expanded_var);
// 	if (!(exp->expanded_string))
// 		(free_exp(exp), free_whole_cshell(cshell), exit(-42));
// 	(free(exp->temp), free(exp->expanded_var));
// 	exp->temp = NULL;
// 	exp->expanded_var = NULL;
// 	exp->cur += exp->varlen;
// }

// char	*double_quotes_expansion(char *line, t_cshell *cshell)
// {
// 	t_exp	exp;

// 	if (is_empty_line(line))
// 		return ("");
// 	if (init_exp(&exp, line) == -42)
// 		(free_exp(&exp), free_whole_cshell(cshell), exit(-42));
// 	while (*(exp.cur) != '"')
// 	{
// 		if (is_valid_exp(exp.cur))
// 			strjoin_expanded_var(&exp, cshell);
// 		else
// 			add_one_char_to_string(&exp, cshell);
// 	}
// 	return (exp.expanded_string);
// }

int	expand_double_quotes(t_exp *exp, t_cshell *cshell, t_token **head)
{
	char    *next_dollar_sign;
	char	*dquote;
	char	*last_bit;

	next_dollar_sign = ft_dquote_strchr(exp->exp_start);
	while (next_dollar_sign)
	{
		exp->exp_str = ft_calloc(next_dollar_sign - exp->exp_start + 1, sizeof(char));
		exp->exp_str = ft_memcpy(exp->exp_str, exp->exp_start, next_dollar_sign - exp->exp_start);
		exp->temp = ft_strjoin();
	}
	exp->temp = exp->exp_str;
	dquote = ft_strchr(exp->exp_start, '"');
	last_bit = ft_calloc(/* some ptr stuff*/, sizeof(char));
	last_bit = ft_memcpy(last_bit, /*  */);
	exp->exp_str = ft_strjoin(exp->temp, last_bit);
	if (!(exp->exp_str))
		return (free_exp(exp), free_tok_chain(head, del_tok_cont), -42);
	exp->exp_strlen = ft_strlen(exp->exp_str);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!(exp->str))
		return (free_exp(exp), free_tok_chain(head, del_tok_cont), -42);
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->exp_strlen;
	return (0);	
}
