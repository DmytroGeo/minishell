/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:15:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/02 11:52:35 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <linux/limits.h>

// this function gets the current working directory and saves it into str.
// no memory problems but I haven't norminetted yet.

char	*pwd(void)
{
	char	buffer[PATH_MAX];
	char	*str;
	str = getcwd(buffer, PATH_MAX);
	return (str);
}