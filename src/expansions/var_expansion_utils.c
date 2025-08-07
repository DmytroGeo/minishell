/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:33:43 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/07 12:54:45 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

int	find_exp_var(t_exp *exp, char **envp)
{
	char	*var;
	char	*exp_var;

	var = ft_calloc(exp->varlen + 1, sizeof(char));
	if (!var)
		return (-42);
	var = ft_memcpy(var, exp->exp_start, exp->varlen);
	exp_var = find_var_in_envp(envp, var);
	free(var);
	if (!exp_var)
		exp->exp_var = NULL;
	else
	{
		exp->exp_var = ft_strdup(exp_var);
		if (!exp->exp_var)
			return (-42);
	}
	return (0);
}

int	find_varlen(const char *str)
{
	int	varlen;

	varlen = 0;
	if (!ft_isalpha(*str) && *str != '_')
		return (varlen);
	varlen++;
	while (ft_isalnum(str[varlen]) || str[varlen] == '_')
		varlen++;
	return (varlen);
}
