/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:37:59 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:13:08 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*strip_quotes(char *str)
{
	size_t	len;
	char	*clean;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	clean = ft_substr(str, 1, len - 2);
	if (!clean)
		return (NULL);
	return (clean);
}

int	is_surrounded_by(char *str, char quote)
{
	size_t	len;
	int		result;

	if (!str || str[0] != quote)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if (str[len - 1] == quote)
		result = 1;
	else
		result = 0;
	return (result);
}
