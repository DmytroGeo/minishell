/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:57:10 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/02 14:16:08 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

void    change_directory(char **new_directory, char **prompt, char **envp)
{
    if (ft_array_len(new_directory) == 1)
    {
        if (chdir(*new_directory) != 0)
        {
            ft_printf(2, "Directory doesn't exist \n");
            return ;        
        }
        *prompt = get_prompt();
    }
    else if (ft_array_len(new_directory) == 0)
    {
        char *home = find_home_variable(envp);
        if (chdir(home) != 0)
        {
            ft_printf(2, "Can't access home directory \n");
            return ;
        }
        *prompt = get_prompt();
    }
    else
        ft_printf(2, "Too many arguments!\n");
    return;        
}