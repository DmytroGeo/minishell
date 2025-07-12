/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:50:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 11:56:27 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_token_content	*init_token_content(char *raw_token, t_op *operators)
{
	t_token_content *content;
	
	content = malloc(sizeof(t_token_content));
	if (!content)
		return (NULL);
	content->value = ft_strdup(raw_token);
    content->type = identify_type(raw_token, operators);
}