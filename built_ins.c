/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:15:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/23 13:11:46 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// this function gets the current working directory and saves it into str.
// no memory problems but I haven't norminetted yet.

char	*get_cwd(void)
{
	char	buffer[PATH_MAX];
	char	*str;
	str = getcwd(buffer, PATH_MAX);
	return (str);
}