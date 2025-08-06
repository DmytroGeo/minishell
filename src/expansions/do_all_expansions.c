/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:18:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/06 17:29:03 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"
#include "lexing.h"

int	do_expansion(t_cshell *cshell, t_exp *exp, t_token **head)
{
	if ((exp->og_str)[exp->i] == '$')
	{
		if (check_and_expand_var(exp, cshell) < 0)
			return (-42);
		return (split_word(head, exp));
	}
	else if ((exp->og_str)[exp->i] == '"')
		return (expand_double_quotes(exp, cshell));
	else if ((exp->og_str)[exp->i] == '\'')
		return (expand_single_quotes(exp));
	return (0);
}

int	identify_expand(t_cshell *cshell, t_exp *exp, t_token **head)
{
	int	c;

	c = (exp->og_str)[exp->i];
	if (c == '"' || c == '\'' || c == '$')
	{
		exp->exp_start = &((exp->og_str)[exp->i + 1]);
		if (do_expansion(cshell, exp, head) < 0)
			return (free_tok_chain(head, del_tok_cont), -42);
	}
	else
	{
		if (add_one_char_to_string(exp, (exp->og_str)[exp->i]) < 0)
			return (free_tok_chain(head, del_tok_cont), -42);
	}
	return (0);
}

t_token	*expand_word(char *value, t_cshell *cshell)
{
	t_token	*head;
	t_exp	exp;

	head = NULL;
	if (init_exp(&exp, value) == -42)
		return (NULL);
	while ((exp.og_str)[exp.i])
	{
		if (identify_expand(cshell, &exp, &head) < 0)
			return (NULL);
	}
	if (add_last_bit_to_list(&head, &exp) < 0)
		return (free_tok_chain(&head, del_tok_cont), NULL);
	free_exp(&exp);
	return (head);
}

t_token	*split_node(t_token	*cur_tok, t_cshell *cshell)
{
	char		*value;
	t_tok_type	type;
	t_token		*new_tok_chain;

	new_tok_chain = NULL;
	type = ((t_tok_cont *)(cur_tok->content))->type;
	if (type != word)
		new_tok_chain = duplicate_current_token(cur_tok);
	else
	{
		value = ((t_tok_cont *)(cur_tok->content))->value;
		new_tok_chain = expand_word(value, cshell);
	}
	return (new_tok_chain);
}

void	do_all_expansions(t_cshell *cshell)
{
	t_token	*cur_tok;
	t_token	*split_token;
	t_token	*new_head;

	cur_tok = cshell->token_chain;
	while (cur_tok->next)
	{
		split_token = split_node(cur_tok, cshell);
		if (!split_token)
		{
			free_tok_chain(&new_head, del_tok_cont);
			(free_whole_cshell(cshell), exit(-42));
		}
		ft_dlstadd_back(&new_head, split_token);
		cur_tok = cur_tok->next;
	}
	free_tok_chain(&(cshell->token_chain), del_tok_cont);
	cshell->token_chain = new_head;
	return ;
}
