/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:57:10 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 14:16:44 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void    change_directory(char **new_directory, char **prompt, char **envp)
{
    if (ft_array_len(new_directory) == 0)
    {
        char *home = getenv("HOME");
        if (!home || chdir(home) != 0)
        {
            ft_printf(2, "Can't access HOME directory \n");
            return ;
        }
    }
    else if (ft_array_len(new_directory) == 1 && ft_strncmp(*new_directory, "-", 2) == 0)
    {
        char *old_directory = getenv("OLDPWD");
        if (!old_directory || chdir(old_directory) != 0)
        {
            
            ft_printf(2, "Can't access OLDPWD\n");
            return ;
        }
    }
    else if (ft_array_len(new_directory) == 1)
    {
        if (chdir(*new_directory) != 0)
        {
            ft_printf(2, "Directory doesn't exist \n");
            return ;        
        }
    }
    else
        ft_printf(2, "Too many arguments!\n");
    // you have to update the OLDPWD and PWD
    *prompt = get_prompt();
    return;        
}