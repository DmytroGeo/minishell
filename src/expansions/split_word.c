/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:48:01 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/17 16:06:14 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "lexing.h"
#include "minishell.h"

int	make_first_token(char *first_space, t_token **head, t_exp *exp)
{
	t_tok_cont	*content;
	int			len;
	t_token		*tok;

	len = first_space - exp->str;
	content = malloc(sizeof(t_tok_cont));
	if (!content)
		return (-42);
	content->value = ft_calloc(len + 1, sizeof(char));
	if (!(content->value))
		return (del_tok_cont((void *)content), -42);
	content->value = ft_memcpy(content->value, exp->str, len);
	content->type = word;
	tok = ft_dlstnew((void *)content);
	if (!tok)
		return (del_tok_cont((void *)content), -42);
	ft_dlstadd_back(head, tok);
	return (0);
}

int	make_and_add_to_the_list(t_token **head, char *str)
{
	t_tok_cont	*content;
	t_token		*tok;

	content = malloc(sizeof(t_tok_cont));
	if (!content)
		return (-42);
	content->value = ft_strdup(str);
	if (!(content->value))
		return (del_tok_cont((void *)content), -42);
	content->type = word;
	tok = ft_dlstnew((void *)content);
	if (!tok)
		return (del_tok_cont((void *)content), -42);
	ft_dlstadd_back(head, tok);
	return (0);
}

int	check_last_token(t_token **head, char *str, t_exp *exp)
{
	int	i;

	i = ft_isspace(*(exp->exp_end));
	exp->exp_start = NULL;
	exp->exp_end = NULL;
	free(exp->str);
	if (i == true)
	{
		if (make_and_add_to_the_list(head, str) < 0)
			return (-42);
		exp->strlen = 0;
		exp->str = NULL;
	}
	else
	{
		exp->strlen = ft_strlen(str);
		exp->str = ft_strdup(str);
		if (!(exp->str))
			return (-42);
	}
	return (0);
}

int	make_rest_of_tokens(char *first_space, t_token **head, t_exp *exp)
{
	char	**array;
	int		array_len;
	int		counter;

	counter = 0;
	array = ft_split(first_space, ' ');
	array_len = ft_array_len(array);
	while (counter < array_len - 1)
	{
		if (make_and_add_to_the_list(head, array[counter]) < 0)
			return (-42);
		counter++;
	}
	if (check_last_token(head, array[counter], exp) < 0)
		return (-42);
	ft_array_free((void **)array);
	return (0);
}

int	split_word(t_token **head, t_exp *exp)
{
	char	*first_space;

	if (exp->exp_start == exp->exp_end)
		return (0);
	first_space = find_first_space(exp);
	if (!first_space)
	{
		exp->exp_start = exp->exp_end;
		return (0);
	}
	if (first_space != exp->str && make_first_token(first_space, head, exp) < 0)
		return (free_exp(exp), -42);
	if (make_rest_of_tokens(first_space, head, exp) < 0)
		return (free_exp(exp), -42);
	return (0);
}
