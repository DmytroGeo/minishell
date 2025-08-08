/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:51:26 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:24:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"
#include "lexing.h"

int	add_last_bit_to_list(t_token **head, t_exp *exp)
{
	t_token		*tok;
	t_tok_cont	*cont;
	int			len;

	cont = malloc(sizeof(t_tok_cont));
	if (!cont)
		return (-42);
	len = exp->strlen;
	cont->value = ft_calloc(len + 1, sizeof(char));
	cont->value = ft_memcpy(cont->value, exp->str, len);
	cont->type = word;
	tok = ft_dlstnew((void *)cont);
	if (!tok)
		return (del_tok_cont((void *)cont), -42);
	ft_dlstadd_back(head, tok);
	return (0);
}

t_token	*duplicate_current_token(t_token *cur_tok)
{
	t_tok_cont	*content;
	t_token		*new_token;

	content = malloc(sizeof(t_tok_cont));
	if (!content)
		return (NULL);
	content->value = ft_strdup(((t_tok_cont *)(cur_tok->content))->value);
	content->type = ((t_tok_cont *)(cur_tok->content))->type;
	new_token = ft_dlstnew(content);
	if (!new_token)
		return (del_tok_cont((void *)content), NULL);
	return (new_token);
}

void	free_exp(t_exp *exp)
{
	free(exp->str);
	exp->exp_str = NULL;
	free(exp->temp);
	exp->temp = NULL;
	free(exp->exp_str);
	exp->exp_str = NULL;
	free(exp->exp_var);
	exp->exp_var = NULL;
}

int	init_exp(t_exp *exp, char *value)
{
	exp->strlen = 0;
	exp->i = 0;
	exp->exp_strlen = 0;
	exp->exp_varlen = 0;
	exp->varlen = 0;
	exp->exp_var = NULL;
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->exp_start = NULL;
	exp->exp_end = NULL;
	exp->og_str = value;
	exp->str = NULL;
	return (0);
}

int	add_one_char_to_string(t_exp *exp, char c)
{
	exp->temp = exp->str;
	exp->str = ft_calloc(exp->strlen + 2, sizeof(char));
	if (!(exp->str))
		return (free_exp(exp), -42);
	exp->str = ft_memcpy(exp->str, exp->temp, exp->strlen);
	(exp->str)[exp->strlen] = c;
	free(exp->temp);
	exp->temp = NULL;
	exp->exp_start = &((exp->str)[exp->strlen]);
	exp->exp_end = exp->exp_start;
	(exp->strlen)++;
	(exp->i)++;
	return (0);
}
