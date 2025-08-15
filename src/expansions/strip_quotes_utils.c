/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:44:18 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/15 17:41:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

void	init_quotes_removal(t_qts_remov	*qts_remov, char *value)
{
	qts_remov->type = '\0';
	qts_remov->i = 0;
	qts_remov->exp_strlen = 0;
	qts_remov->strlen = 0;
	qts_remov->str = NULL;
	qts_remov->exp_str = NULL;
	qts_remov->next_quote = NULL;
	qts_remov->temp = NULL;
	qts_remov->og_string = value;
	qts_remov->current = value;
}

void	free_quotes_removal(t_qts_remov *qts_remov)
{
	qts_remov->type = '\0';
	qts_remov->i = 0;
	qts_remov->strlen = 0;
	qts_remov->exp_strlen = 0;
	free(qts_remov->str);
	qts_remov->str = NULL;
	free(qts_remov->exp_str);
	qts_remov->exp_str = NULL;
	free(qts_remov->temp);
	qts_remov->temp = NULL;
}

void	add_one_char_to_str(t_qts_remov *qts_remov)
{
	char	c;

	c = *(qts_remov->current);
	qts_remov->temp = qts_remov->str;
	qts_remov->str = ft_calloc(qts_remov->strlen + 2, sizeof(char));
	qts_remov->str = ft_memcpy(qts_remov->str, qts_remov->temp, \
			qts_remov->strlen);
	if (!(qts_remov->str))
		return (free_quotes_removal(qts_remov), exit(-42));
	(qts_remov->str)[qts_remov->strlen] = c;
	free(qts_remov->temp);
	qts_remov->temp = NULL;
	qts_remov->i += 1;
	qts_remov->current += 1;
	qts_remov->strlen += 1;
}

void	copy_in_str_cont(t_qts_remov *qts_remov, int c)
{
	qts_remov->next_quote = ft_strchr(qts_remov->current, c);
	qts_remov->exp_strlen = qts_remov->next_quote - qts_remov->current;
	qts_remov->exp_str = ft_calloc(qts_remov->exp_strlen + 1, sizeof(char));
	qts_remov->exp_str = ft_memcpy(qts_remov->exp_str, qts_remov->current, \
			qts_remov->exp_strlen);
	if (!(qts_remov->exp_str))
		return (free_quotes_removal(qts_remov), exit(-42));
	qts_remov->temp = qts_remov->str;
	qts_remov->str = ft_strjoin(qts_remov->temp, qts_remov->exp_str);
	free(qts_remov->temp);
	free(qts_remov->exp_str);
	qts_remov->temp = NULL;
	qts_remov->exp_str = NULL;
	qts_remov->i += qts_remov->exp_strlen + 1;
	qts_remov->current += qts_remov->exp_strlen + 1;
	qts_remov->strlen += qts_remov->exp_strlen;
}

void	get_in_string_cont(t_qts_remov *qts_remov)
{
	int	c;

	c = *(qts_remov->current);
	if (*(qts_remov->current + 1) == c)
	{
		qts_remov->i += 2;
		qts_remov->current += 2;
	}
	else
	{
		qts_remov->i += 1;
		qts_remov->current += 1;
		copy_in_str_cont(qts_remov, c);
	}
}
