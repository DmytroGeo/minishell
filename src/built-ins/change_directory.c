/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:57:10 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 12:02:32 by dgeorgiy         ###   ########.fr       */
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
	home = find_var_in_envp(*envp, "HOME");
	if (!home || chdir(home) != 0)
	{
		ft_printf(2, "Can't access HOME directory \n");
		free(current_pwd);
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
	old_pwd = find_var_in_envp(*envp, "OLDPWD");
	if (!old_pwd || chdir(old_pwd) != 0)
	{
		ft_printf(2, "Can't access OLDPWD\n");
		free(current_pwd);
		return (-1);
	}
	change_prompt_and_envp(prompt, envp, current_pwd);
	free(current_pwd);
	return (0);
}

int	new_dir(char **prompt, char ***envp, char *new_directory)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (chdir(new_directory) != 0)
	{
		ft_printf(2, "Directory doesn't exist\n");
		free(current_pwd);
		return (-1);
	}
	change_prompt_and_envp(prompt, envp, current_pwd);
	free(current_pwd);
	return (0);
}

void	ft_chdir(char **args, t_cshell *cshell)
{
	int	num_of_args;

	num_of_args = ft_array_len(args);
	if (num_of_args == 0)
	{
		cshell->exec_code = go_to_home(&(cshell->prompt), &(cshell->envp));
		return ;
	}
	else if (num_of_args == 1 && ft_strncmp(*args, "-", 2) == 0)
	{
		cshell->exec_code = go_back(&(cshell->prompt), &(cshell->envp));
		return ;
	}
	else if (num_of_args == 1)
	{
		cshell->exec_code = new_dir(&(cshell->prompt), &(cshell->envp), *args);
		return ;
	}
	ft_printf(2, "minishell: cd: too many arguments\n");
	cshell->exec_code = 1;
}
