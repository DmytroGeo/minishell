/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:27:45 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/23 13:23:46 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

int	export_variable(char ***envp, char *assignment)
{
	char	**new_envp;
	char	*key;
	int		index;
	char	*equals_sign;

	equals_sign = ft_strchr(assignment, '=');
	if (equals_sign)
		key = ft_substr(assignment, 0, equals_sign - assignment);
	else
		key = assignment;
	index = find_envp_index(*envp, key);
	free(key);
	if (index >= 0 && equals_sign)
		new_envp = replace_existing_var(*envp, index, assignment);
	else if (index < 0)
		new_envp = export_new_var(*envp, assignment);
	else
		return (0);
	int n = ft_array_len(*envp);
	int k = ft_array_len(new_envp);
	ft_printf(2, "Number of vars before: %d\n", n);
	ft_printf(2, "Number of vars after: %d\n", k);
	char **temp = new_envp;
	while (*temp)
	{
		ft_printf(2, "%s\n", *temp);
		temp++;
	}
	ft_array_free((void **)*envp);
	if (!new_envp)
		return (-2);
	*envp = new_envp;
	return (0);
}

int	export_all_vars(char **arguments, char ***envp, int fd)
{
	int	exit_code;

	exit_code = 0;
	if (ft_array_len(arguments) == 0)
	{
		print_export(*envp, fd);
		return (exit_code);
	}
	while (*arguments)
	{
		if (is_valid_variable_assignment(*arguments))
		{
			exit_code = export_variable(envp, *arguments);
			if (exit_code == -2)
				return (exit_code);
		}
		else
			ft_printf(2, "Invalid export format: %s\n", *arguments);
		arguments++;
	}
	return (exit_code);
}
