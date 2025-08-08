/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:27:45 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 19:47:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

void	print_export(char **envp, int fd)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		ft_printf(fd, "declare -x ");
		ft_printf(fd, "%s\n", envp[i]);
		i++;
	}
	return ;
}

char	**replace_existing_var(char **envp, int index, char *assignment)
{
	char	**new_envp;
	int		envp_len;
	int		i;

	envp_len = ft_array_len(envp);
	new_envp = ft_calloc(sizeof(char *), (envp_len + 1));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (++i < envp_len)
	{
		if (i == index)
			new_envp[i] = ft_strdup(assignment);
		else
			new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (ft_array_free((void **)new_envp), NULL);
	}
	return (new_envp);
}

char	**export_new_var(char **envp, char *assignment)
{
	char	**new_envp;
	int		envp_len;
	int		i;

	envp_len = ft_array_len(envp);
	new_envp = ft_calloc(sizeof(char *), (envp_len + 2));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (++i < envp_len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (ft_array_free((void **)new_envp), NULL);
	}
	new_envp[envp_len] = ft_strdup(assignment);
	if (!new_envp[envp_len])
		return (ft_array_free((void **)new_envp), NULL);
	return (new_envp);
}

/**
 * @brief This function exports the value of assignment to envp.
 * A new list is created and the old one is freed.
 * Then we set the envp attribute of cshell to point to the head of our new list.
 * @param address_of_envp The address of our copy of envp
 * @param assignment the current argument of export (e.g a=hello)
 * @return 0 for success and -42 for memory failure.
 */
int	export_variable(char ***address_of_envp, char *assignment)
{
	char	**new_envp;
	char	*key;
	int		index;
	char	*equals_sign;

	equals_sign = ft_strchr(assignment, '=');
	if (equals_sign)
	{
		key = ft_substr(assignment, 0, equals_sign - assignment);
		index = find_envp_index(*address_of_envp, key);
		free(key);
	}
	else
		index = find_envp_index(*address_of_envp, assignment);
	if (index >= 0 && equals_sign)
		new_envp = replace_existing_var(*address_of_envp, index, assignment);
	else if (index < 0)
		new_envp = export_new_var(*address_of_envp, assignment);
	else
		return (0);
	ft_array_free((void **)*address_of_envp);
	if (!new_envp)
		return (-42);
	*address_of_envp = new_envp;
	return (0);
}

/**
 * @brief If export is given no arguments, it prints the list of all
 * variables, even those that don't have a value. Otherwise, if export is
 * given arguments, it exports them one at a time, as long as the key
 * (variable name) is valid.
 * @param cshell The main 'cshell' structure.
 * @param arguments the arguments of export.
 * @param outfile_fd the file descriptor to write to.
 * @return nothing - this is a void function.
 */
void	export_all_vars(char **arguments, t_cshell *cshell, int outfile_fd)
{
	if (ft_array_len(arguments) == 0)
	{
		cshell->exit_code = 0;
		return (print_export(cshell->envp, outfile_fd));
	}
	while (*arguments)
	{
		if (is_valid_variable_assignment(*arguments))
		{
			cshell->exit_code = export_variable(&(cshell->envp), *arguments);
			if (cshell->exit_code == -42)
				(free_whole_cshell(cshell), exit(-42));
		}
		else
			return ;
		arguments++;
	}
}
