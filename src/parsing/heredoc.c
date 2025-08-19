/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:18:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/19 11:50:01 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"

extern volatile sig_atomic_t	g_received_signal;

int	line_matches_limiter(char *limiter, char *line_read)
{
	int	limiter_len;
	int	line_read_len;
	int	i;
	int	j;

	limiter_len = ft_strlen(limiter);
	line_read_len = ft_strlen(line_read);
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
	free(temp);
	fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	free(file_name);
	return (fd);
}

int	reopen_heredoc(int heredoc_number)
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
	free(temp);
	fd = open(file_name, O_RDONLY);
	free(file_name);
	return (fd);
}

void	heredoc_eof_err(const char *limiter)
{
	ft_printf(2, "minishell: warning: here-document delimited by ");
	ft_printf(2, "end-of-file (wanted '%s')\n", limiter);
}

int	heredoc_fd(char *limiter, int i, t_cshell *cshell)
{
	char		*line_read;
	int			fd;

	set_heredoc_signals();
	fd = create_heredoc(cshell->num_heredocs);
	while (1)
	{
		line_read = readline("> ");
		if (g_received_signal == SIGINT)
		{
			line_read = NULL;
		}
		if (!line_read)
		{
			heredoc_eof_err(limiter);
			break ;
		}
		if (line_matches_limiter(limiter, line_read))
			break ;
		if (i == true)
			line_read = heredoc_expand(line_read, cshell);
		(ft_printf(fd, "%s\n", line_read), free(line_read));
	}
	close(fd);
	fd = reopen_heredoc(cshell->num_heredocs);
	cshell->num_heredocs++;
	return (fd);
}
