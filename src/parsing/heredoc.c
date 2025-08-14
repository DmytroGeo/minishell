/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/14 20:37:13 by dgeorgiy         ###   ########.fr       */
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

int	create_heredoc(int heredoc_number)
{
	char	*file_name;
	char	*number_string;
	char	*temp;
	int		fd;

	number_string = ft_itoa(heredoc_number);
	file_name = ft_strjoin(".heredoc", number_string);
	free(number_string);
	temp = file_name;
	file_name = ft_strjoin(temp, ".tmp");
	fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	return (fd);
}

int	heredoc_fd(char *limiter, int i, t_cshell *cshell)
{
	char		*line_read;
	int			fd;

	fd = create_heredoc(cshell->num_heredocs);
	cshell->num_heredocs++;
	while (1)
	{
		line_read = readline("> ");
		if (line_read)
		{
			if (i == true)
				line_read = heredoc_expand(line_read, cshell->envp);
			if (line_matches_limiter(limiter, line_read))
				break ;
			else
				write(fd, line_read, ft_strlen(line_read));
		}
		else
			break ;
		free(line_read);
	}
	return (fd);
}
