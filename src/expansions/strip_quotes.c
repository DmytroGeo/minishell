/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 05:51:54 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/14 08:59:32 by dgeorgiy         ###   ########.fr       */
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
	content->value = ft_strdup(stripped_quotes_string);
	content->type = word;
	new_token = ft_dlstnew(content);
	if (!new_token)
		return (del_tok_cont((void *)content), NULL);
	new_token->exp_needed = true;
	return (new_token);
}

t_token	*strip_quotes(char *value)
{
	char	*stripped_quotes_string;
	t_token	*new_token;
	int		contains_quotes;

	new_token = NULL;
	contains_quotes = (find_next_quote(value) != NULL);
	stripped_quotes_string = quotes_removal(value);
	new_token = make_new_tok(stripped_quotes_string);
	free(stripped_quotes_string);
	if (contains_quotes == true)
		new_token->exp_needed = false;
	return (new_token);
}
