/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_some_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:42:50 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/09 11:13:47 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_eof(t_token *current_token)
{
	return (current_token->type == end_of_file);
}

int	is_variable(t_token *current_token)
{
	return (current_token->type == variable);
}

int	is_word(t_token *current_token)
{
	return (current_token->type == word);
}

int	is_pipe(t_token *current_token)
{
	return (current_token->type == _pipe);
}

int	is_operator(t_token *current_token)
{
	return (is_redir_in(current_token)
		|| is_heredoc(current_token)
		|| is_redir_out(current_token)
		|| is_append(current_token));
}
