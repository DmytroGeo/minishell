/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:10:27 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 11:53:03 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	copy_envp(char ***address_of_copy, char **envp)
{
	int		i;
	char	**copy;

	if (!envp)
		return (0);
	i = 0;
	copy = ft_calloc(sizeof(char *), (ft_array_len(envp) + 1));
	if (!copy)
		return (-42);
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

int	get_prompt(char **address_of_prompt)
{
	char	*cwd;
	char	*temp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	temp = ft_strjoin("minishell:", cwd);
	if (!temp)
		return (-42);
	free(cwd);
	prompt = ft_strjoin(temp, "$ ");
	if (!prompt)
		return (free(temp), -42);
	free(temp);
	free(*address_of_prompt);
	*address_of_prompt = prompt;
	return (0);
}

void	init_cshell(t_cshell *cshell, char **envp)
{
	cshell->parse_code = 0;
	cshell->exec_code = 0;
	cshell->pid = NULL;
	cshell->fd = NULL;
	cshell->proc_array = NULL;
	cshell->token_chain = NULL;
	cshell->prompt = NULL;
	cshell->envp = NULL;
	cshell->shell_id = 0;
	cshell->parse_code = copy_envp(&(cshell->envp), envp);
	if (cshell->parse_code == -42)
		exit(-42);
	cshell->parse_code = get_prompt(&(cshell->prompt));
	if (cshell->parse_code == -42)
		return (free_whole_cshell(cshell), exit(-42));
	return ;
}
