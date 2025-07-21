/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_all_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:32:48 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 15:59:35 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	unset_all_vars(char **arguments, char ***envp)
{
	while (*arguments)
	{
		unset_variable(envp, *arguments);
		arguments++;
	}
	return (0);
}
