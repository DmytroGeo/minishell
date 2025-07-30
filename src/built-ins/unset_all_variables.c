/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_all_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:32:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/30 13:24:15 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

int	find_envp_index(char **envp, const char *key)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	unset_variable(char ***envp, char *key)
{
	int		i;
	int		index;
	char	**new_envp;

	index = find_envp_index(*envp, key);
	i = -1;
	new_envp = ft_calloc(sizeof(char *), ft_array_len(*envp));
	if (!new_envp)
		return (-42);
	while (++i < index)
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (!(new_envp[i]))
			return (ft_array_free((void **)new_envp), -42);
	}
	while (i < ft_array_len(*envp) - 1)
	{
		new_envp[i] = ft_strdup((*envp)[i + 1]);
		if (!(new_envp[i]))
			return (ft_array_free((void **)new_envp), -42);
		i++;
	}
	ft_array_free((void **)*envp);
	*envp = new_envp;
	return (0);
}

void	unset_all_vars(char **arguments, t_cshell *cshell)
{

	if (ft_array_len(arguments) == 0)
		return ;
	while (*arguments)
	{
		if (is_valid_var_unset(*arguments)
			&& find_envp_index(cshell->envp, *arguments) >= 0)
		{
			cshell->exit_code = unset_variable(&(cshell->envp), *arguments);
			if (cshell->exit_code == -42)
				(free_whole_cshell(cshell), exit(-42));
		}
		arguments++;
	}
}
