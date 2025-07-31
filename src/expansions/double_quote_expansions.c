/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_expansions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:05:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 11:54:43 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

int	init_exp(t_exp *exp, char *line)
{
	exp->expanded_strlen = 1;
	exp->cur = line + 1;
	exp->i = 0;
	exp->temp = NULL;
	exp->expanded_var = NULL;
	exp->expanded_string = ft_calloc(exp->expanded_strlen + 1, sizeof(char));
	if (!(exp->expanded_string))
		return (-42);
	return (0);
}

void	add_one_char_to_string(t_exp *exp, t_cshell *cshell)
{
	exp->expanded_strlen++;
	exp->temp = exp->expanded_string;
	exp->expanded_string = ft_calloc(exp->expanded_strlen + 1, sizeof(char));
	if (!(exp->expanded_string))
		(free_exp(exp), free_whole_cshell(cshell), exit(-42));
	exp->expanded_string = ft_memcpy(exp->expanded_string,
			exp->temp, exp->expanded_strlen - 1);
	free(exp->temp);
	exp->temp = NULL;
	exp->expanded_string[exp->expanded_strlen - 1] = *(exp->cur);
	exp->cur++;
}

char	*find_var(const char *var, int varlen)
{
	char	*key;

	key = ft_calloc(varlen + 1, sizeof(char));
	if (!key)
		return (NULL);
	key = ft_memcpy(key, var, varlen);
	return (key);
}

void	strjoin_expanded_var(t_exp *exp, t_cshell *cshell)
{
	char	*var;

	exp->varlen = find_varlen(exp->cur + 1);
	if (exp->varlen == 1 && *(exp->cur + 1) == '?')
		exp->expanded_var = ft_itoa(cshell->exec_code);
	else if (exp->varlen == 1 && *(exp->cur + 1) == '$')
		exp->expanded_var = ft_itoa(cshell->shell_id);
	else
	{
		var = find_var(exp->cur + 1, exp->varlen);
		if (!var)
			(free_exp(exp), free_whole_cshell(cshell), exit(-42));
		exp->expanded_var = ft_strdup(find_var_in_envp(cshell->envp, var));
		free(var);
	}
	if (!(exp->expanded_string))
		(free_exp(exp), free_whole_cshell(cshell), exit(-42));
	exp->temp = exp->expanded_string;
	exp->expanded_string = ft_strjoin(exp->temp, exp->expanded_var);
	if (!(exp->expanded_string))
		(free_exp(exp), free_whole_cshell(cshell), exit(-42));
	(free(exp->temp), free(exp->expanded_var));
	exp->temp = NULL;
	exp->expanded_var = NULL;
	exp->cur += exp->varlen;
}

char	*double_quotes_expansion(char *line, t_cshell *cshell)
{
	t_exp	exp;

	if (is_empty_line(line))
		return ("");
	if (init_exp(&exp, line) == -42)
		(free_exp(&exp), free_whole_cshell(cshell), exit(-42));
	while (*(exp.cur) != '"')
	{
		if (is_valid_exp(exp.cur))
			strjoin_expanded_var(&exp, cshell);
		else
			add_one_char_to_string(&exp, cshell);
	}
	return (exp.expanded_string);
}
