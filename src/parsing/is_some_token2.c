/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_some_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:41:03 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:11:59 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_heredoc(t_token *current_token)
{
	t_tok_cont	*content;

	if (!current_token)
		return (false);
	content = (t_tok_cont *)(current_token->content);
	return (content->type == heredoc);
}

int	is_redir_in(t_token *current_token)
{
	t_tok_cont	*content;

	if (!current_token)
		return (false);
	content = (t_tok_cont *)(current_token->content);
	return (content->type == redir_in);
}

int	is_redir_out(t_token *current_token)
{
	t_tok_cont	*content;

	if (!current_token)
		return (false);
	content = (t_tok_cont *)(current_token->content);
	return (content->type == redir_out);
}

int	is_append(t_token *current_token)
{
	t_tok_cont	*content;

	if (!current_token)
		return (false);
	content = (t_tok_cont *)(current_token->content);
	return (content->type == append);
}
