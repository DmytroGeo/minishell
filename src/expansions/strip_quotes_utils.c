/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 06:44:18 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/14 19:16:17 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"

void	init_quotes_removal(t_qts_remov	*qts_remov, char *value)
{
	qts_remov->type = '\0';
	qts_remov->i = 0;
	qts_remov->len = 0;
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
	free(qts_remov->str);
	qts_remov->str = NULL;
	free(qts_remov->exp_str);
	qts_remov->exp_str = NULL;
	free(qts_remov->temp);
	qts_remov->temp = NULL;
}

void	get_in_string_cont(t_qts_remov *qts_remov)
{
	if (qts_remov->next_quote)
		qts_remov->len = qts_remov->next_quote - qts_remov->current;
	else
		qts_remov->len = ft_strlen(qts_remov->current);
	if (qts_remov->len > 0)
	{
		qts_remov->exp_str = ft_calloc(qts_remov->len + 1, sizeof(char));
		if (!(qts_remov->exp_str))
			return (free_quotes_removal(qts_remov), exit(-42));
		qts_remov->exp_str = ft_memcpy(qts_remov->exp_str, qts_remov->current, \
			qts_remov->len);
		qts_remov->strlen += qts_remov->len;
		qts_remov->temp = qts_remov->str;
		qts_remov->str = ft_strjoin(qts_remov->temp, qts_remov->exp_str);
		if (!(qts_remov->str))
			return (free_quotes_removal(qts_remov), exit(-42));
		free(qts_remov->exp_str);
		free(qts_remov->temp);
		qts_remov->exp_str = NULL;
		qts_remov->temp = NULL;
	}
	qts_remov->i += qts_remov->len + 1;
	qts_remov->current = &((qts_remov->og_string)[qts_remov->i]);
}

char	*find_next_quote(const char *s)
{
	size_t			n;
	char			*str;

	str = (char *)s;
	n = 0;
	while (str[n] != '\0')
	{
		if (str[n] == '"' || str[n] == '\'')
			return (str + n);
		n++;
	}
	return (NULL);
}
