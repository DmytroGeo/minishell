/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_conditions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:17:53 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 14:08:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	syntax_check_1(t_token *curr)
{
	return (is_redirect(curr) && !is_word(curr->next));
}

int	syntax_check_2(t_token *curr)
{
	return (is_pipe(curr) && !(curr->previous));
}

int	syntax_check_3(t_token *curr)
{
	return (is_pipe(curr)
		&& !(is_word(curr->next) || is_redirect(curr->next)));
}

int	syntax_check_4(t_token *curr)
{
	return (is_pipe(curr) && !(curr->next));
}
