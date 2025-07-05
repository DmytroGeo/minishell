/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:01:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:28:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	free_simple_command(t_simple_command *simple_command)
{
	if (simple_command->commands)
		ft_array_free(simple_command->commands, ft_array_len(simple_command->commands));
	if (simple_command->infiles)
		ft_intarr_free(simple_command->infiles, ft_int_array_len(simple_command->infiles));
	if (simple_command->outfiles)
		ft_intarr_free(simple_command->outfiles, ft_int_array_len(simple_command->outfiles));
	if (simple_command->address_of_envp)
		free(simple_command->address_of_envp);
	if (simple_command->address_of_prompt)
		free(simple_command->address_of_prompt);
	return (0);
}

