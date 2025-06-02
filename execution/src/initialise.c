/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/01 13:49:52 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// void	init_list(int ac, char **av, char **envp, t_list **head)
// {
// 	int		i;
// 	t_list	*temp_node;
// 	t_execution_content *temp_content;
// 	char	**array;
// 	char	*path;
// 	char	**flags;

// 	i = ac - 1;
// 	temp_node = NULL;
// 	temp_content = NULL;
// 	while (i > 2)
// 	{
// 		i--;
// 		array = ft_split(av[i], ' ');
// 		if (access(array[0], F_OK | X_OK) == 0)
// 			path = ft_strdup(array[0]);
// 		else
// 			path = get_path(array[0], envp);
// 		if (!path)
// 			ft_perror(array[0], 'p');
// 		flags = get_flags(&array[1]);
// 		temp_content = ft_init_content(path, flags, ac, envp);
// 		temp_content->index = i - 2;
// 		temp_content->av = av;
// 		temp_node = ft_lstnew(temp_content);
// 		(ft_lstadd_front(head, temp_node), ft_array_free(array, ft_array_len(array)));
// 	}
// }

void	init_list(int number_of_commands, char **commands, char **envp, t_list **head)
{
    int		i;
	t_list	*temp_node;
	t_execution_content *temp_content;
	char	**array;
	char	*path;
	char	**flags;

	i = number_of_commands;
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
		if (!path)
			ft_perror(array[0], 'p');
		flags = get_flags(&array[1]);
		temp_content = ft_init_content(path, flags, number_of_commands, envp);
		temp_content->index = i;
		temp_node = ft_lstnew(temp_content);
		(ft_lstadd_front(head, temp_node), ft_array_free(array, ft_array_len(array)));
	}
}

void	init_setup(int **pid, int ***fd, int number_of_commands, t_list **head)
{
	int	i;

	i = -1;
	*pid = malloc((number_of_commands) * sizeof(int));
	if (!*pid)
		return ;
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
