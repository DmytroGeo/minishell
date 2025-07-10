/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:01:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/08 10:43:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	free_simple_command(t_simple_command *simple_command)
{
	ft_array_free(simple_command->commands, ft_array_len(simple_command->commands));
	ft_intarr_free(simple_command->infiles, ft_int_array_len(simple_command->infiles));
	ft_intarr_free(simple_command->outfiles, ft_int_array_len(simple_command->outfiles));
	// free(simple_command->address_of_envp);
	free(simple_command);
	return (0);
}

