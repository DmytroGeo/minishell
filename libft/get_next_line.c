/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:14:14 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/02 15:01:09 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_and_append(int fd, char **str, char *buffer)
{
	char		*tmp;
	char		*r_str;
	ssize_t		bytes_read;

	r_str = ft_strchr(*str, '\n');
	while (r_str == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(*str, buffer);
		free(*str);
		*str = tmp;
		r_str = ft_strchr(*str, '\n');
	}
	return (r_str);
}

char	*finalise_line(char *str, char *buffer)
{
	char	*r_str;
	char	*tmp;

	if (ft_strlen(str) == 0)
	{
		free(str);
		return (NULL);
	}
	r_str = ft_strchr(str, '\n');
	if (r_str != NULL)
	{
		ft_memcpy(buffer, r_str + 1, ft_strlen(r_str));
		buffer[ft_strlen(r_str)] = '\0';
		*(r_str + 1) = '\0';
		tmp = ft_strdup(str);
		free(str);
		str = tmp;
	}
	else
		buffer[0] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	str = ft_strdup(buffer);
	if (read_and_append(fd, &str, buffer) == NULL && ft_strlen(str) == 0)
	{
		free(str);
		return (NULL);
	}
	return (finalise_line(str, buffer));
}
