/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 05:51:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/15 17:39:23 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"
#include "lexing.h"

t_token	*make_new_tok(char *stripped_quotes_string)
{
	t_token		*new_token;
	t_tok_cont	*content;

	content = malloc(sizeof(t_tok_cont));
	if (!content)
		return (NULL);
	content->value = stripped_quotes_string;
	content->type = word;
	new_token = ft_dlstnew(content);
	if (!new_token)
		return (del_tok_cont((void *)content), NULL);
	new_token->exp_needed = true;
	return (new_token);
}

char	*quotes_removal(char *value)
{
	t_qts_remov	qts_remov;
	char		*stripped_quotes_string;

	init_quotes_removal(&qts_remov, value);
	while ((qts_remov.og_string)[qts_remov.i])
	{
		if (*(qts_remov.current) == '\'' || *(qts_remov.current) == '"')
			get_in_string_cont(&qts_remov);
		else
			add_one_char_to_str(&qts_remov);
	}
	stripped_quotes_string = ft_strdup(qts_remov.str);
	free_quotes_removal(&qts_remov);
	return (stripped_quotes_string);
}

t_token	*strip_quotes(char *value)
{
	char	*stripped_quotes_string;
	t_token	*new_token;
	int		contains_quotes;

	new_token = NULL;
	contains_quotes = (ft_strchr(value, '\'') != NULL
			|| ft_strchr(value, '"') != NULL);
	stripped_quotes_string = quotes_removal(value);
	new_token = make_new_tok(stripped_quotes_string);
	if (contains_quotes == true)
		new_token->exp_needed = false;
	return (new_token);
}
