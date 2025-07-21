/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:53:52 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 10:35:27 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_cwd(void)
{
	char	buffer[PATH_MAX];
	char	*str;

	str = getcwd(buffer, PATH_MAX);
	return (str);
}

char	*get_prompt(void)
{
	char	*cwd;
	char	*temp;
	char	*prompt;

	cwd = ft_get_cwd();
	temp = ft_strjoin("minishell:", cwd);
	prompt = ft_strjoin(temp, "$ ");
	free(temp);
	return (prompt);
}
