/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:57:10 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 17:49:50 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	change_prompt_and_envp(char **prompt, char ***envp, char *old_pwd)
{
	char	*old_directory;
	char	*new_directory;
	char	*cwd;

	get_prompt(prompt);
	cwd = getcwd(NULL, 0);
	old_directory = ft_strjoin("OLDPWD=", old_pwd);
	new_directory = ft_strjoin("PWD=", cwd);
	export_variable(envp, old_directory);
	export_variable(envp, new_directory);
	free(old_directory);
	free(new_directory);
	free(cwd);
	return ;
}

int	go_to_home(char **prompt, char ***envp)
{
	char	*home;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	home = find_variable_in_envp(*envp, "HOME");
	if (!home || chdir(home) != 0)
	{
		ft_printf(2, "Can't access HOME directory \n");
		return (-1);
	}
	change_prompt_and_envp(prompt, envp, current_pwd);
	free(current_pwd);
	return (0);
}

int	go_back(char **prompt, char ***envp)
{
	char	*old_pwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	old_pwd = find_variable_in_envp(*envp, "OLDPWD");
	if (!old_pwd || chdir(old_pwd) != 0)
	{
		ft_printf(2, "Can't access OLDPWD\n");
		return (-1);
	}
	change_prompt_and_envp(prompt, envp, current_pwd);
	free(current_pwd);
	return (0);
}

int	go_to_new_directory(char **prompt, char ***envp, char *new_directory)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (chdir(new_directory) != 0)
	{
		ft_printf(2, "Directory doesn't exist\n");
		return (-1);
	}
	change_prompt_and_envp(prompt, envp, current_pwd);
	free(current_pwd);
	return (0);
}

int	ft_chdir(char **arguments, char **prompt, char ***envp)
{
	int	num_of_args;

	num_of_args = ft_array_len(arguments);
	if (num_of_args == 0)
		return (go_to_home(prompt, envp));
	else if (num_of_args == 1 && ft_strncmp(*arguments, "-", 2) == 0)
		return (go_back(prompt, envp));
	else if (num_of_args == 1)
		return (go_to_new_directory(prompt, envp, *arguments));
	else
		return (ft_printf(2, "Too many arguments!\n"), -1);
	return (0);
}
