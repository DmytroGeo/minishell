/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:01:11 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 17:02:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	proc_call(int i, char c)
{
	if ((c == 'o' || c == 'i') && i < 0)
		perror(NULL);
	else if (c == 'a' && i < 0)
		perror("Can't access file");
	return (0);
}