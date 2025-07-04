/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_functs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:51:57 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 17:56:04 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_env_index(char **envp, const char *key)
{
	int		i = 0;
	size_t	len = ft_strlen(key);

	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	unset_variable(char ***envp, const char *key)
{
	int		i = 0;
	int		j = 0;
	int		index = find_env_index(*envp, key);
	char	**new_env;

	if (index < 0)
		return;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * i); // one less

	i = 0;
	while ((*envp)[i])
	{
		if (i == index)
			free((*envp)[i]);
		else
			new_env[j++] = (*envp)[i];
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	*envp = new_env;
}

void	export_variable(char ***envp, const char *assignment)
{
	char	**new_env;
	char	*key;
	int		i = 0;
	int		index;

	key = ft_substr(assignment, 0, ft_strchr(assignment, '=') - assignment);
	index = find_env_index(*envp, key);
	free(key);

	if (index >= 0)
	{
		free((*envp)[index]);
		(*envp)[index] = ft_strdup(assignment);
	}
	else
	{
		while ((*envp)[i])
			i++;
		new_env = malloc(sizeof(char *) * (i + 2));
		i = 0;
		while ((*envp)[i])
		{
			new_env[i] = (*envp)[i];
			i++;
		}
		new_env[i] = ft_strdup(assignment);
		new_env[i + 1] = NULL;
		free(*envp);
		*envp = new_env;
	}
}

void copy_envp(char ***envp)
{
	int		i;
	char	**copy;

	if (!*envp)
		return ;
	i = 0;
	while ((*envp)[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		copy[i] = ft_strdup((*envp)[i]);
		i++;
	}
	copy[i] = NULL;
	*envp = copy;
	return ;
}

int	is_valid_variable_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char *find_variable_name(char *str)
{
	char *equal_sign = ft_strchr(str, '=');
	char *variable_name = malloc(sizeof(char) * (equal_sign - str + 1));
	ft_memcpy(variable_name, str, equal_sign - str);
	variable_name[equal_sign - str] = '\0';
	return (variable_name);
}

int	is_valid_variable_assignment(char *str)
{
	int		i;
	char	*equal_sign;
	char	*variable_name;
	int n;

	if (!str)
		return (0);
	variable_name = find_variable_name(str);
	n = is_valid_variable_name(variable_name);
	free(variable_name);
	if (n == 0)
		return (0);
	// Find '=' in the string
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign/* || equals == str || *(equals + 1) == '\0'*/)
		return (0); // no '=' → not a variable assignment

	// Check for space around '='
	if (equal_sign == str || equal_sign[-1] == ' ' || equal_sign[1] == ' ')
		return (0); // starts with '=' or has space around it

	// Check the name before '='
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (&str[i] < equal_sign)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}