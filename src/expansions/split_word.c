/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:48:01 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/04 17:13:56 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "lexing.h"
#include "minishell.h"

t_tok_cont	*init_new_word(char *raw_token)
{
	t_tok_cont	*content;

	content = malloc(sizeof(t_tok_cont));
	if (!content)
		return (NULL);
	content->value = ft_strdup(raw_token);
	content->type = word;
	return (content);
}

int	split_word(t_token **head, t_exp *exp)
{
	char		*new_word;
	t_tok_cont	*content;
	t_token		*new;

	new_word = get_new_word(exp);
	while (new_word)
	{
		content = init_new_word(new_word);
		if (!content)
			return (free_exp(exp), -42);
		new = ft_dlstnew((void *)content);
		if (!new)
			return (del_tok_cont((void *)content), free_exp(exp), -42);
		ft_dlstadd_back(head, new);
		new_word = get_new_word(exp);
	}
	return (0);
}