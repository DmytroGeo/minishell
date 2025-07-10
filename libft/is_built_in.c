/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:08:50 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/07 12:53:05 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_built_in(char *str)
{
    if (ft_strncmp(str, "cd", 3) == 0)
        return(true);
    else if (ft_strncmp(str, "exit", 5) == 0)
        return(true);
    else if (ft_strncmp(str, "export", 7) == 0) 
        return(true);
    else if (ft_strncmp(str, "unset", 6) == 0)
        return(true);
    else if (ft_strncmp(str, "env", 4) == 0)
        return(true);
    else if (ft_strncmp(str, "pwd", 4) == 0)
        return(true);
    else if (ft_strncmp(str, "echo", 5) == 0)
        return(true);
    else
        return (false);
}