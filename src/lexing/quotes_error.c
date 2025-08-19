/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:28:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/07 17:54:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "minishell.h"

int	quotes_error(int num_squotes, int num_dquotes)
{
	if (num_squotes % 2 == 1)
	{
		ft_printf(2, "minishell: syntax error: unclosed single quotes\n");
		return (1);
	}
	if (num_dquotes % 2 == 1)
	{
		ft_printf(2, "minishell: syntax error: unclosed double quotes\n");
		return (1);
	}
	return (0);
}

void	count_qts(t_qts *qts, int c)
{
	if (c == '\'' && qts->in_squotes == true)
	{
		qts->num_squotes++;
		qts->in_squotes = false;
	}
	else if (c == '\'' && qts->in_squotes == false && qts->in_dquotes == false)
	{
		qts->num_squotes++;
		qts->in_squotes = true;
	}
	else if (c == '"' && qts->in_dquotes == true)
	{
		qts->num_dquotes++;
		qts->in_dquotes = false;
	}
	else if (c == '"' && qts->in_dquotes == false && qts->in_squotes == false)
	{
		qts->num_dquotes++;
		qts->in_dquotes = true;
	}
	return ;
}

void	init_qts(t_qts *qts)
{
	qts->num_squotes = 0;
	qts->num_dquotes = 0;
	qts->in_dquotes = false;
	qts->in_squotes = false;
	return ;
}

int	wrong_number_of_quotes(t_cshell *cshell)
{
	char	*curr;
	t_qts	qts;

	init_qts(&qts);
	curr = cshell->line_read;
	while (*curr)
	{
		count_qts(&qts, *curr);
		curr++;
	}
	return (quotes_error(qts.num_squotes, qts.num_dquotes));
}
