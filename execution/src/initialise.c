/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:41:49 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 09:58:10 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	init_list(int ac, char **av, char **envp, t_list **head)
{
	int		i;
	t_list	*temp;
	char	**array;
	char	*path;
	char	**flags;

	i = ac - 1;
	temp = NULL;
	while (i > 2)
	{
		i--;
		array = ft_split(av[i], ' ');
		if (access(array[0], F_OK | X_OK) == 0)
			path = ft_strdup(array[0]);
		else
			path = get_path(array[0], envp);
		if (!path)
			ft_perror(array[0], 'p');
		flags = get_flags(&array[1]);
		temp = ft_lstnew(path, flags, ac, envp);
		temp->index = i - 2;
		temp->av = av;
		ft_lstadd_front(head, temp);
		ft_array_free(array);
	}
}

void	init_setup(int **pid, int ***fd, int ac, t_list **head)
{
	int	i;

	i = -1;
	*pid = malloc((ac - 3) * sizeof(int));
	if (!*pid)
		return ;
	*fd = malloc((ac - 4) * sizeof(int *));
	if (!*fd)
		return ;
	while (++i < ac - 4)
	{
		(*fd)[i] = malloc(2 * sizeof(int));
		if (!(*fd)[i])
		{
			perror("fd malloc failed");
			(free(*pid), ft_intarr_free(*fd, i), ft_lstclear(head));
			exit (EXIT_FAILURE);
		}
		if (pipe((*fd)[i]) < 0)
		{
			(perror (NULL), free(*pid));
			(close_fds(*fd, i + 1), ft_intarr_free(*fd, i), ft_lstclear(head));
			exit (EXIT_FAILURE);
		}
	}
}
