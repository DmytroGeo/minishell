/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:01:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 13:25:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_simple_command(t_simple_command *simple_command)
{
	if (simple_command->commands)
		ft_array_free(simple_command->commands, ft_array_len(simple_command->commands));
	if (simple_command->infiles)
		ft_intarr_free(simple_command->infiles, ft_intarr_len(simple_command->infiles));
	if (simple_command->outfiles)
		ft_intarr_free(simple_command->outfiles, ft_intarr_len(simple_command->outfiles));
	// free envp
	// free 	
}