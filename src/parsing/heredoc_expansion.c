/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:52:33 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/14 19:27:34 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "expansions.h"
#include "minishell.h"

void	copy_up_to_dollar_sign(t_hd_exp *hd_exp)
{
	if (hd_exp->next_dollar_sign)
		hd_exp->non_var_len = hd_exp->next_dollar_sign - hd_exp->current;
	else
		hd_exp->non_var_len = ft_strlen(hd_exp->current);
	if (hd_exp->non_var_len > 0)
	{
		hd_exp->non_var_str = ft_calloc(hd_exp->non_var_len + 1, sizeof(char));
		if (!(hd_exp->non_var_str))
			return (free_hd_exp(hd_exp), exit(-42));
		hd_exp->non_var_str = ft_memcpy(hd_exp->non_var_str, hd_exp->current, \
			hd_exp->non_var_len);
		hd_exp->strlen += hd_exp->non_var_len;
		hd_exp->temp = hd_exp->str;
		hd_exp->str = ft_strjoin(hd_exp->temp, hd_exp->non_var_str);
		if (!(hd_exp->str))
			return (free_hd_exp(hd_exp), exit(-42));
		free(hd_exp->non_var_str);
		free(hd_exp->temp);
		hd_exp->non_var_str = NULL;
		hd_exp->temp = NULL;
	}
	hd_exp->i += hd_exp->non_var_len + 1;
	hd_exp->current = &((hd_exp->og_string)[hd_exp->i]);
}

int	hd_find_exp_var(t_hd_exp *hd_exp, char **envp)
{
	char	*var;
	char	*exp_var;

	var = ft_calloc(hd_exp->varlen + 1, sizeof(char));
	if (!var)
		return (-42);
	var = ft_memcpy(var, hd_exp->current, hd_exp->varlen);
	exp_var = find_var_in_envp(envp, var);
	free(var);
	if (!exp_var)
		hd_exp->exp_var = NULL;
	else
	{
		hd_exp->exp_var = ft_strdup(exp_var);
		if (!hd_exp->exp_var)
			return (-42);
	}
	return (0);
}

void	expand_var(t_hd_exp *hd_exp, char **envp)
{
	hd_exp->i += hd_exp->varlen;
	hd_exp->current += hd_exp->varlen;
	hd_find_exp_var(hd_exp, envp);
	if (hd_exp->exp_var)
	{
		hd_exp->temp = hd_exp->str;
		hd_exp->str = ft_strjoin(hd_exp->temp, hd_exp->exp_var);
		if (!(hd_exp->str))
			return (free_hd_exp(hd_exp), exit(-42));
		(free(hd_exp->temp), free(hd_exp->exp_var));
		hd_exp->temp = NULL;
		hd_exp->exp_var = NULL;
		hd_exp->strlen += hd_exp->exp_varlen;
	}
}

void	expand_dollar_sign(t_hd_exp *hd_exp, char **envp)
{
	char	c;

	hd_exp->i++;
	hd_exp->current++;
	c = *(hd_exp->current);
	if (c == ' ' || c == '\0' || c == '\'' || c == '"')
	{
		hd_exp->temp = hd_exp->str;
		hd_exp->str = ft_strjoin(hd_exp->temp, "$");
		if (!(hd_exp->str))
			return (free_hd_exp(hd_exp), exit(-42));
		hd_exp->temp = NULL;
		hd_exp->strlen++;
		return ;
	}
	hd_exp->varlen = find_varlen(hd_exp->current);
	if (hd_exp->varlen == 0)
	{
		hd_exp->i++;
		hd_exp->current++;
		return ;
	}
	expand_var(hd_exp, envp);
}

char	*heredoc_expand(char *str, char **envp)
{
	t_hd_exp	hd_exp;
	char		*expanded_string;

	init_hd_exp(&hd_exp, str);
	while ((hd_exp.og_string)[hd_exp.i])
	{
		hd_exp.next_dollar_sign = ft_strchr(hd_exp.current, '$');
		copy_up_to_dollar_sign(&hd_exp);
		if (hd_exp.next_dollar_sign)
			expand_dollar_sign(&hd_exp, envp);
	}
	expanded_string = ft_strdup(hd_exp.str);
	free(str);
	str = NULL;
	free_hd_exp(&hd_exp);
	return (expanded_string);
}
