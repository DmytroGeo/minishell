/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 12:26:53 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		heredoc_fd(char *limiter)
{
	int *fd;
	int read_end;
	char *line_read;
	
	read_end = -42;
	fd = malloc(2 * sizeof(int));
	if (!fd)
		return (read_end);
	pipe(fd);
	while (1)
	{
		write(1, "> ", 2);
		line_read = get_next_line(0);
		if (ft_strncmp(line_read, limiter, ft_strlen(limiter)) == 0 && ft_strncmp(line_read, limiter, ft_strlen(line_read) - 1) == 0)
		{
			read_end = fd[0];
			close(fd[1]);        
			break ;
		}
		else
			write(fd[1], line_read, ft_strlen(line_read));
	}
	return (read_end);
}