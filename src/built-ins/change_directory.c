/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:57:10 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/11 12:55:16 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

/**
 * @brief This function updates the $OLDPWD and $PWD in
 * our copy of envp after cd is run.
 * @param prompt The address of current prompt.
 * @param envp The address of environment list.
 * @param old_pwd The current $PWD.
 * @return nothing - this is a void function.
 */
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

/**
 * @brief This function attempts to change the current directory
 * to the home directory $HOME. In case it doesn't work, print error.
 * If it does exist, update prompt and the $PWD and $OLDPWD entries 
 * in the environment.
 * @param address_of_prompt The address of current prompt.
 * @param address_of_envp The address of environment list.
 * @return returns 0 on success and 1 on failure 
 * (if new_directory doesn't exist).
 */
int	go_to_home(char **address_of_prompt, char ***address_of_envp)
{
	char	*home;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	home = find_var_in_envp(*address_of_envp, "HOME");
	if (!home || chdir(home) != 0)
	{
		ft_printf(2, "minishell: cd: HOME not set\n");
		free(current_pwd);
		return (1);
	}
	change_prompt_and_envp(address_of_prompt, address_of_envp, current_pwd);
	free(current_pwd);
	return (0);
}

/**
 * @brief This function attempts to change the current directory
 * to the old directory $OLDPWD. In case it doesn't work, print error.
 * If it does exist, update prompt and the $PWD and $OLDPWD entries 
 * in the environment.
 * @param address_of_prompt The address of current prompt.
 * @param address_of_envp The address of environment list.
 * @return returns 0 on success and 1 on failure 
 * (if new_directory doesn't exist).
 */
int	go_back(char **address_of_prompt, char ***address_of_envp)
{
	char	*old_pwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	old_pwd = find_var_in_envp(*address_of_envp, "OLDPWD");
	if (!old_pwd || chdir(old_pwd) != 0)
	{
		ft_printf(2, "minishell: cd: OLDPWD not set\n");
		free(current_pwd);
		return (1);
	}
	change_prompt_and_envp(address_of_prompt, address_of_envp, current_pwd);
	free(current_pwd);
	return (0);
}

/**
 * @brief This function attempts to change the current directory
 * to the new directory new_dir. In case it doesn't work, print error.
 * If it does exist, update prompt and the $PWD and $OLDPWD entries 
 * in the environment.
 * @param address_of_prompt The address of current prompt.
 * @param address_of_envp The address of environment list.
 * @param new_dir The new directory we want ot change to.
 * @return returns 0 on success and 1 on failure 
 * (if new_directory doesn't exist).
 */
int	new_dir(char **address_of_prompt, char ***address_of_envp, char *new_dir)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (chdir(new_dir) != 0)
	{
		existence_error(new_dir);
		free(current_pwd);
		return (1);
	}
	change_prompt_and_envp(address_of_prompt, address_of_envp, current_pwd);
	free(current_pwd);
	return (0);
}

/**
 * @brief This function changes current directory.
 * If no arguments are given, it takes us back to $HOME.
 * If only '-' is given, it takes us to $OLDPWD.
 * If any other argument is given, it takes us to that directory.
 * If more than one argument is given, print error message.
 * @param args The arguments of cd
 * @param cshell The main 'cshell' structure.
 * @return void function.
 */
void	ft_chdir(char **args, t_cshell *cshell)
{
	int	num_of_args;

	num_of_args = ft_array_len(args);
	if (num_of_args == 0)
	{
		cshell->exit_code = go_to_home(&(cshell->prompt), &(cshell->envp));
		return ;
	}
	else if (num_of_args == 1 && ft_strncmp(*args, "-", 2) == 0)
	{
		cshell->exit_code = go_back(&(cshell->prompt), &(cshell->envp));
		return ;
	}
	else if (num_of_args == 1)
	{
		cshell->exit_code = new_dir(&(cshell->prompt), &(cshell->envp), *args);
		return ;
	}
	ft_printf(2, "minishell: cd: too many arguments\n");
	cshell->exit_code = 1;
}
