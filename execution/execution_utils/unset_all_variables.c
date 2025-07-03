/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_all_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:32:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/01 09:28:11 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	unset_all_variables(char **arguments, char ***envp)
{
	while (*arguments)
	{
		unset_variable(envp, *arguments);
		arguments++;
	}
}