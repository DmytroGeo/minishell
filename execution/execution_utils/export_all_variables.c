/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:27:45 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/02 13:51:35 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	export_all_variables(char **arguments, char ***envp)
{
	while (*arguments)
	{
		if (is_valid_variable_assignment(*arguments))
			export_variable(envp, *arguments);
		else
			ft_printf(2, "Invalid export format: %s\n", *arguments);
		arguments++;
	}
}