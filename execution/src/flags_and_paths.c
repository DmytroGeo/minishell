/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_and_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:30:41 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/31 17:32:47 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*find_path_variable(char **envp)
{
	char	**ptr;
	char	*path_variable;

	ptr = envp;
	while (*ptr)
	{
		if ((ft_strnstr(*ptr, "PATH", ft_strlen(*ptr)) && **ptr == 'P'))
			break ;
		ptr++;
	}
	if (*ptr == NULL)
	{
		ft_perror("", 'p');
		return (NULL);
	}
	path_variable = *ptr;
	path_variable += ft_strlen("PATH=");
	return (path_variable);
}

char	*get_path(char *str, char **envp)
{
	char	*path_variable;
	char	*temp1;
	char	*temp2;
	char	**arr;
	int		i;

	i = -1;
	path_variable = find_path_variable(envp);
	if (!path_variable)
		return (NULL);
	arr = ft_split(path_variable, ':');
	while (arr[++i])
	{
		temp1 = ft_strjoin(arr[i], "/");
		temp2 = ft_strjoin(temp1, str);
		free(temp1);
		if (access(temp2, F_OK | X_OK) == 0)
		{
			ft_array_free(arr, ft_array_len(arr));
			return (temp2);
		}
		free(temp2);
	}
	ft_array_free(arr, ft_array_len(arr));
	return (NULL);
}

char	**get_flags(char **arr)
{
	char	**flags;
	int		i;
	int		len;

	i = 0;
	len = ft_array_len(arr);
	if (len == 0)
		return (NULL);
	flags = malloc((len + 1) * sizeof(char *));
	if (!flags)
		return (NULL);
	while (i < len)
	{
		flags[i] = malloc(ft_strlen(arr[i]) + 1);
		if (!flags[i])
			return (ft_array_free(flags, i));
		flags[i] = ft_strcpy(flags[i], arr[i]);
		i++;
	}
	flags[i] = NULL;
	return (flags);
}
