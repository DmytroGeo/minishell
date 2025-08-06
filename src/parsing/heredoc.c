/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/06 17:35:25 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	line_matches_limiter(char *limiter, char *line_read)
{
	int	limiter_len;
	int	line_read_len;
	int	i;
	int	j;

	limiter_len = ft_strlen(limiter);
	line_read_len = ft_strlen(line_read) - 1;
	i = ft_strncmp(line_read, limiter, limiter_len);
	j = ft_strncmp(line_read, limiter, line_read_len);
	return (i == 0 && j == 0);
}

int	heredoc_fd(char *limiter)
{
	(void)limiter;
	return (0);
}
	// int		*fd;
	// int		read_end;
	// char	*line_read;

	// read_end = -42;
	// fd = malloc(2 * sizeof(int));
	// if (!fd)
	// 	return (read_end);
	// pipe(fd);
	// while (1)
	// {
	// 	line_read = readline("> ");
	// 	if (line_read)
	// 	{
	// 		if (line_matches_limiter(limiter, line_read))
	// 		{
	// 			read_end = fd[0];
	// 			close(fd[1]);
	// 			break ;
	// 		}
	// 		else
	// 			write(fd[1], line_read, ft_strlen(line_read));
	// 	}
	// 	else
	// 		break ;
	// }
	// return (read_end);
