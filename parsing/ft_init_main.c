/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:10:27 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/23 12:09:06 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	copy_envp(char ***address_of_copy, char **envp)
{
	int		i;
	char	**copy;

	if (!envp)
		return (0);
	i = 0;
	copy = ft_calloc(sizeof(char *), (ft_array_len(envp) + 1));
	if (!copy)
		return (-2);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!(copy[i]))
			return (ft_array_free((void **)copy), -2);
		i++;
	}
	*address_of_copy = copy;
	return (0);
}

char	*ft_get_cwd(void)
{
	char	buffer[PATH_MAX];
	char	*str;

	str = getcwd(buffer, PATH_MAX);
	return (str);
}

int	get_prompt(char **address_of_prompt)
{
	char	*cwd;
	char	*temp;
	char	*prompt;

	cwd = ft_get_cwd();
	temp = ft_strjoin("minishell:", cwd);
	if (!temp)
		return (-2);
	prompt = ft_strjoin(temp, "$ ");
	if (!prompt)
		return (free(temp), -2);
	free(temp);
	free(*address_of_prompt);
	*address_of_prompt = prompt;
	return (0);
}

void	init_cshell(t_cshell *cshell, char **envp)
{
	int	exit_code;

	exit_code = 0;
	cshell->pid = NULL;
	cshell->fd = NULL;
	cshell->proc_array = NULL;
	cshell->token_chain = NULL;
	cshell->prompt = NULL;
	cshell->envp = NULL;
	exit_code = copy_envp(&(cshell->envp), envp);
	if (exit_code == -2)
		exit(-42);
	exit_code = get_prompt(&(cshell->prompt));
	if (exit_code == -2)
		return (free_cshell(cshell), exit(-42));
	return ;
}
