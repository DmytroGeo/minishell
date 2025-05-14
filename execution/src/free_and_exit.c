/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:29:36 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 09:56:17 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_and_exit(int *pid, int **fd, t_list **head)
{
	int		ac;

	if (!fd)
		return ;
	ac = (*head)->ac;
	free(pid);
	ft_intarr_free(fd, ac - 4);
	ft_lstclear(head);
	return ;
}
