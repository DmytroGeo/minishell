/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:48:01 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/11 10:56:23 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "lexing.h"
#include "minishell.h"

t_tok_cont	*init_new_word_cont(t_exp *exp, char *new_space)
{
	t_tok_cont	*content;
	int			len;

	content = malloc(sizeof(t_tok_cont));
	len = new_space - exp->exp_str;
	if (!content)
		return (NULL);
	content->value = ft_calloc(len + 1, sizeof(char));
	content->value = ft_memcpy(content->value, exp->exp_str, len);
	content->type = word;
	return (content);
}

char	*find_next_space(t_exp *exp)
{
	char	*current;

	current = exp->exp_start;
	while (!ft_isspace(*current) && current != exp->exp_end)
		current++;
	if (current == exp->exp_end)
		return (NULL);
	exp->exp_start = current;
	while (!ft_isspace(*(exp->exp_start)) && exp->exp_start != exp->exp_end)
		exp->exp_start++;
	return (current);
}

int	init_new_word(char *new_space, t_token **head, t_exp *exp)
{
	t_tok_cont	*content;
	t_token		*tok;

	content = init_new_word_cont(exp, new_space);
	if (!content)
		return (-42);
	tok = ft_dlstnew((void *)content);
	if (!tok)
		return (del_tok_cont((void *)content), -42);
	ft_dlstadd_back(head, tok);
	exp->strlen = ft_strlen(exp->exp_start);
	exp->temp = exp->str;
	exp->str = ft_calloc(exp->strlen, sizeof(char));
	if (!(exp->str))
		return (-42);
	exp->str = ft_memcpy(exp->str, exp->exp_start, exp->strlen);
	free(exp->temp);
	exp->temp = NULL;
	return (0);
}

int	split_word(t_token **head, t_exp *exp)
{
	char	*new_space;

	if (exp->exp_start == exp->exp_end)
		return (0);
	new_space = find_next_space(exp);
	if (!new_space)
		return (0);
	while (new_space)
	{
		if (init_new_word(new_space, head, exp) < 0)
			return (free_exp(exp), -42);
		new_space = find_next_space(exp);
	}
	return (0);
}
