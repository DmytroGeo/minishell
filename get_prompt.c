/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:53:52 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/27 10:55:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*get_cwd(void)
{
	char	buffer[PATH_MAX];
	char	*str;
	str = getcwd(buffer, PATH_MAX);
	return (str);
}

char *get_prompt(void)
{
    char *cwd = get_cwd();
    char *temp = ft_strjoin("minishell:", cwd);
    char *prompt = ft_strjoin(temp, "$ ");
    free(temp);
    return(prompt);
}