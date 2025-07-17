/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:56:43 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 11:45:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_and_exit(int *pid, int **fd, t_main *main)
{
	free(pid);
	ft_array_free2((void **)fd, main->num_of_proc - 1);
	free_main(main);
}