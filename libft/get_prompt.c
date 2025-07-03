/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:53:52 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/01 11:01:53 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char	*ft_get_cwd(void)
{
	char	buffer[PATH_MAX];
	char	*str;
	str = getcwd(buffer, PATH_MAX);
	return (str);
}

char *get_prompt(void)
{
    char *cwd = ft_get_cwd();
    char *temp = ft_strjoin("minishell:", cwd);
    char *prompt = ft_strjoin(temp, "$ ");
    // char **address_of_prompt = malloc(sizeof(char *));
    // address_of_prompt = &prompt;
    free(temp);
    return(prompt);
}