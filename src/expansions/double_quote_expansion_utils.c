/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_expansion_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:51:00 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/10 20:45:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_dollar_strchr(const char *s)
{
	size_t	n;
	char	*str;

	str = (char *)s;
	n = 0;
	while (str[n] != '\0' && str[n] != '"')
	{
		if (str[n] == '$')
			return (str + n);
		n++;
	}
	return (NULL);
}

int	expand_var_in_dquotes(t_exp *exp, t_cshell *cshell)
{
	if (find_exp_var(exp, cshell->envp) < 0)
		return (free_exp(exp), -42);
	if (exp->exp_var)
	{
		exp->exp_varlen = ft_strlen(exp->exp_var);
		exp->temp = exp->exp_str;
		exp->exp_str = ft_strjoin(exp->temp, exp->exp_var);
		if (!(exp->exp_str))
			return (free_exp(exp), -42);
		free(exp->temp);
		free(exp->exp_var);
		exp->temp = NULL;
		exp->exp_var = NULL;
		exp->exp_strlen += exp->exp_varlen;
	}
	exp->i += exp->varlen + 1;
	return (0);
}
