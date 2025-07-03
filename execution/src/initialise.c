/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 19:08:24 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	init_list(t_simple_command *simple_command, char **commands, char **envp)
{
    int		i;
	char	**array;

	i = ft_array_len(simple_command->commands);
	while (i > 0)
	{
		i--;
		array = ft_split(commands[i], ' ');
		if (access(array[0], F_OK | X_OK) == 0)
			path = ft_strdup(array[0]);
		else
			path = get_path(array[0], envp);
		if (!path && !is_built_in(array[0]))
			ft_perror(array[0], 'p');
		temp_content->command_name = ft_strdup(array[0]);
	}
}

void	init_setup(int **pid, int ***fd, t_simple_command *simple_command)
{
	int	i;
	int number_of_commands = ft_array_len(simple_command->commands);
	i = -1;
	*pid = malloc((number_of_commands) * sizeof(int));
	if (!*pid)
		return ;
	if (number_of_commands == 0)
		*fd = malloc(0 * sizeof(int *));
	else 
		*fd = malloc((number_of_commands - 1) * sizeof(int *));
	if (!*fd)
		return ;
	while (++i < number_of_commands - 1)
	{
		(*fd)[i] = malloc(2 * sizeof(int));
		if (!(*fd)[i])
		{
			perror("fd malloc failed");
			(free(*pid), ft_intarr_free(*fd, i), /* We have to free the t_simple_command*/);
			exit (EXIT_FAILURE);
		}
		if (pipe((*fd)[i]) < 0)
		{
			(perror (NULL), free(*pid));
			(close_fds(*fd, i + 1), ft_intarr_free(*fd, i), /* We have to free the t_simple_command*/);
			exit (EXIT_FAILURE);
		}
	}
}
