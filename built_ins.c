/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:02:06 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/27 13:01:33 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	evaluate_built_ins(t_token *token_chain, int *exit_status, char **prompt)
{
	if (ft_strncmp(token_chain->value, "cd", 3) == 0 && !is_EOF(token_chain->next)) // this doesn't work for smth like cd | > outfile
	{
		change_directory(token_chain->next->value, prompt);
		return (EXIT_SUCCESS);			
	}
	else if ((ft_strncmp(token_chain->value, "cd", 3) == 0 && is_EOF(token_chain->next)))
	{
		change_directory("..", prompt); // this needs to be edited. cd has to take you to home or root (Whatever "~" is).
		return (EXIT_SUCCESS);		
	}
	else if (ft_strncmp(token_chain->value, "$?", 3) == 0)
	{
		ft_printf("%d\n", *exit_status);	
		return (EXIT_SUCCESS);		
	}
	else
		return (EXIT_FAILURE);	
}
