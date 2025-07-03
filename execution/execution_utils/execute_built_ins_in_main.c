/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins_in_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:12:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/02 17:25:50 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute_built_ins_in_main(t_simple_command *simple_command, char ***envp, char **prompt)
{
	int outfile_fd = 1;
	if (simple_command->outfiles)
		outfile_fd = *((simple_command->outfiles)[ft_int_array_len(simple_command->outfiles) - 1]);
	execute_built_ins(*(simple_command->commands), outfile_fd, envp, prompt);
}