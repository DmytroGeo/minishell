/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_all_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:32:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 19:59:42 by dgeorgiy         ###   ########.fr       */
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

/**
 * @brief This function unsets the variable with the key 'key'.
 * A new list is created and the old one is freed.
 * Then we set the envp attribute of cshell to point to the head of our new list.
 * @param address_of_envp The address of our copy of envp
 * @param key the variable name.
 * @return 0 for success and -42 for memory failure.
 */
int	unset_variable(char ***address_of_envp, char *key)
{
	int		i;
	int		index;
	char	**new_envp;

	index = find_envp_index(*address_of_envp, key);
	i = -1;
	new_envp = ft_calloc(sizeof(char *), ft_array_len(*address_of_envp));
	if (!new_envp)
		return (-42);
	while (++i < index)
	{
		new_envp[i] = ft_strdup((*address_of_envp)[i]);
		if (!(new_envp[i]))
			return (ft_array_free((void **)new_envp), -42);
	}
	while (i < ft_array_len(*address_of_envp) - 1)
	{
		new_envp[i] = ft_strdup((*address_of_envp)[i + 1]);
		if (!(new_envp[i]))
			return (ft_array_free((void **)new_envp), -42);
		i++;
	}
	ft_array_free((void **)*address_of_envp);
	*address_of_envp = new_envp;
	return (0);
}

/**
 * @brief Otherwise, if unset is given arguments, it unsets them one at a time,
 * in a loop as long as it can find them. Note that, to unset a variable, only
 * the key is needed. So the only command that unsets a=hello is 'unset a'.
 * Each time a variable is unset, a new, modified copy of envp is created and
 * the old one is freed.
 * @param cshell The main 'cshell' structure.
 * @param arguments the arguments of unset.
 * @return nothing - this is a void function.
 */
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
