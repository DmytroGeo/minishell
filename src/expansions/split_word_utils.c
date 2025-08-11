/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:00:18 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/11 20:29:37 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "lexing.h"
#include "minishell.h"

char	*find_first_space(t_exp *exp)
{
	char	*current;

	current = exp->exp_start;
	while (!ft_isspace(*current) && current != exp->exp_end)
		current++;
	if (current == exp->exp_end)
		return (NULL);
	exp->exp_start = current;
	return (current);
}
