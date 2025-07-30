/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:03:42 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/29 11:04:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*single_quotes_expansion(char *line)
{
	char	*next_single_quote;
	int		i;
	char	*modified_line;

	next_single_quote = ft_strchr(line, '\'');
	i = 0;
	modified_line = ft_calloc(next_single_quote - line, sizeof(char));
	while (i < next_single_quote - line - 1)
	{
		modified_line[i] = line[i + 1];
		i++;
	}
	return (modified_line);
}
