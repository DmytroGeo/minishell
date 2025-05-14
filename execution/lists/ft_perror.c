/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:09:15 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:39 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

void	ft_perror(char *str, char c)
{
	int		p;
	char	*temp1;
	char	*temp2;
	char	*error_message;

	p = 2;
	if (c == 'p')
		error_message = "PATH not found";
	else if (c == 'o')
		error_message = "my zsh: no such file or directory: ";
	else
		error_message = "my zsh: command not found: ";
	temp1 = ft_strjoin(error_message, str);
	if (!temp1)
		return ;
	temp2 = ft_strjoin(temp1, "\n");
	if (!temp2)
	{
		free(temp1);
		return ;
	}
	ft_putstr_fd(temp2, p, &p);
	free(temp1);
	free(temp2);
	return ;
}
