/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_some_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:42:50 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 12:28:15 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_eof(t_token *current_token)
{
	return (current_token && current_token->next == NULL);
}

int	is_word(t_token *current_token)
{
	t_token_content	*content;

	if (!current_token)
		return (false);
	content = (t_token_content *)(current_token->content);
	return (content->type == word);
}

int	is_pipe(t_token *current_token)
{
	t_token_content	*content;

	if (!current_token)
		return (false);
	content = (t_token_content *)(current_token->content);
	return (content->type == _pipe);
}

int	is_redirect(t_token *current_token)
{
	return (is_redir_in(current_token)
		|| is_heredoc(current_token)
		|| is_redir_out(current_token)
		|| is_append(current_token));
}
