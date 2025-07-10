/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_number_of_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:37:16 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/10 13:39:46 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// this function finds the number of infiles.
// if ANY of the infiles havedon't exist or have the wrong permissions,
// we return -1. This tells find_infiles() to return -1 to parsing and not execute the process.

int find_number_of_infiles(t_token *start)
{
	int	number_of_infiles;
	
	number_of_infiles = 0;
	while (!is_eof(start) && !is_pipe(start))
	{
		if (is_heredoc(start) || is_redir_in(start))
		{
			start = start->next;
			if (is_heredoc(start->previous) && !is_valid_heredoc_name(start->value))
				return (ft_printf(2, "minishell: syntax error near unexpected token '%s'\n", start->value), -1);
			else if (is_redir_in(start->previous) && !access(start->value, F_OK))
				return (ft_printf(2, "minishell: %s: No such file or directory\n", start->value), -1);
			else if (is_redir_in(start->previous) && !access(start->value, R_OK))
				return (ft_printf(2, "minishell: %s: Permission denied\n", start->value), -1);
			else
				number_of_infiles++;
		}
		start = start->next;
	}										
	return (number_of_infiles);
}