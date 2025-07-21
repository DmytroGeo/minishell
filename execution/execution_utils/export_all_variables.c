/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:27:45 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 15:59:25 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	export_all_vars(char **arguments, char ***envp)
{
	while (*arguments)
	{
		if (is_valid_variable_assignment(*arguments))
			export_variable(envp, *arguments);
		else
			ft_printf(2, "Invalid export format: %s\n", *arguments);
		arguments++;
	}
	return (0);
}
