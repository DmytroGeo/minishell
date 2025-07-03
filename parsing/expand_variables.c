/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:18:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 11:18:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void expand_variables(t_token **token_chain, int exit_status, char **envp)
{
	t_token *current_token;
	(void)exit_status;
	(void)envp;
	current_token = *token_chain;
	while (!is_EOF(current_token))
	{
		if (is_variable(current_token))
			ft_printf(1, "There's a variable\n");
		else if (is_single_quotes(current_token))
			ft_printf(1, "There's a single-quoted string\n");
		else if (is_double_quotes(current_token))
			ft_printf(1, "There's a double-quoted string\n");	
		current_token = current_token->next;
	}
}