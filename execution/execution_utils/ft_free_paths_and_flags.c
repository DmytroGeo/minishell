/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_paths_and_flags.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:12:05 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/31 17:12:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_free_paths_and_flags(void *content)
{
	t_execution_content *to_free;

	to_free = (t_execution_content *)content;
	free(to_free->path);
	ft_array_free(to_free->flags, ft_array_len(to_free->flags));
	free(to_free);
}