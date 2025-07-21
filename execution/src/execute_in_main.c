/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:41:31 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 10:52:39 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_in_main(t_cshell *cshell)
{
	int	exit_status;

	exit_status = execute_built_ins(cshell, 0);
	free_cshell(cshell);
	return (exit_status);
}
