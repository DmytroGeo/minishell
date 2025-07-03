/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:37:59 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 16:41:17 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexing.h"

char *strip_quotes(char *str)
{
    size_t  len;
    char    *clean;

    if (!str)
        return (NULL);

    len = ft_strlen(str);
    if (len < 2)
        return (ft_strdup(str)); // nothing to strip

    // remove the first and last character (the quotes)
    clean = ft_substr(str, 1, len - 2);
    if (!clean)
        return (NULL); // memory allocation failed

    return (clean);
}

int is_surrounded_by(char *str, char quote)
{
    size_t len;
    int result;

    if (!str || str[0] != quote)
    {
        // ft_printf(1, "%s\n", str);
        // ft_printf(1, "The first character is not a quote\n");
        return (0);        
    }
 // doesn't start with quote
    len = ft_strlen(str);
    if (len < 2)
        return (0); // too short to have both quotes

    if (str[len - 1] == quote)
        result = 1;
    else
        result = 0;
    return (result);
}