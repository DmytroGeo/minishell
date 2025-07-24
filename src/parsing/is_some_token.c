/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_some_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:42:50 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/24 12:52:41 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(t_token *current_token)
{
	t_tok_cont	*content;

	if (!current_token)
		return (false);
	content = (t_tok_cont *)(current_token->content);
	return (content->type == word);
}

int	is_pipe(t_token *current_token)
{
	t_tok_cont	*content;

	if (!current_token)
		return (false);
	content = (t_tok_cont *)(current_token->content);
	return (content->type == _pipe);
}

int	is_redirect(t_token *current_token)
{
	return (is_redir_in(current_token)
		|| is_heredoc(current_token)
		|| is_redir_out(current_token)
		|| is_append(current_token));
}
