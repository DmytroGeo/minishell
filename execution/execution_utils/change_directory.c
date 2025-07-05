/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:57:10 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 13:41:33 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int    change_directory(char **new_directory, char **prompt, char ***envp)
{
    char *home;
    char *old_pwd;
    char *pwd_before_cd;
    char *pwd_after_cd;

    pwd_before_cd = ft_strjoin("OLDPWD=", find_variable_in_envp(*envp, "PWD"));  
    if (ft_array_len(new_directory) == 0)
    {
        home = find_variable_in_envp(*envp, "HOME");
        if (!home || chdir(home) != 0)
        {
            ft_printf(2, "Can't access HOME directory \n");
            free(pwd_before_cd);
            return (-1);
        }
        free(home);
    }
    else if (ft_array_len(new_directory) == 1 && ft_strncmp(*new_directory, "-", 2) == 0)
    {
        old_pwd = find_variable_in_envp(*envp, "OLDPWD");
        if (!old_pwd || chdir(old_pwd) != 0)
        {
            ft_printf(2, "Can't access OLDPWD\n");
            free(pwd_before_cd);
            return (-1);
        }
        free(old_pwd);
    }
    else if (ft_array_len(new_directory) == 1)
    {
        if (chdir(*new_directory) != 0)
        {
            ft_printf(2, "Directory doesn't exist\n");
            free(pwd_before_cd);
            return (-1);        
        }
    }
    else
    {
        ft_printf(2, "Too many arguments!\n");
        free(pwd_before_cd);
        return (-1);
    }
    pwd_after_cd = ft_strjoin("PWD=", ft_get_cwd());
    export_variable(envp, pwd_after_cd);
    export_variable(envp, pwd_before_cd);
    (free(pwd_after_cd), free(pwd_before_cd));
    *prompt = get_prompt();
    return (0);        
}