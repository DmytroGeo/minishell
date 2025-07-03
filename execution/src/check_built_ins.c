/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:15:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/28 17:49:46 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int		check_built_ins(t_simple_command *simple_command)
{
	char **array = ft_split(*(simple_command->commands), ' ');
	int i = 0;
	if (is_built_in(*array))
		i += 1;
	ft_array_free(array, ft_array_len(array));
	return (i);
}