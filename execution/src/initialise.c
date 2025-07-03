/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/01 09:11:34 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	init_list(t_simple_command *simple_command, char **commands, char **envp, t_list **head)
{
    int		i;
	t_list	*temp_node;
	t_execution_content *temp_content;
	char	**array;
	char	*path;
	char	**flags;

	i = ft_array_len(simple_command->commands);
	temp_node = NULL;
	temp_content = NULL;
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
		flags = get_flags(&array[1]);
		temp_content = ft_init_content(path, flags, ft_array_len(simple_command->commands), envp);
		temp_content->index = i;
		temp_content->command_name = ft_strdup(array[0]);
		// temp_content->address_of_prompt = simple_command->address_of_prompt;
		temp_node = ft_lstnew(temp_content);
		(ft_lstadd_front(head, temp_node), ft_array_free(array, ft_array_len(array)));
	}
}

void	init_setup(int **pid, int ***fd, t_simple_command *simple_command, t_list **head)
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
			(free(*pid), ft_intarr_free(*fd, i), ft_lstclear(head, ft_free_paths_and_flags));
			exit (EXIT_FAILURE);
		}
		if (pipe((*fd)[i]) < 0)
		{
			(perror (NULL), free(*pid));
			(close_fds(*fd, i + 1), ft_intarr_free(*fd, i), ft_lstclear(head, ft_free_paths_and_flags));
			exit (EXIT_FAILURE);
		}
	}
}
