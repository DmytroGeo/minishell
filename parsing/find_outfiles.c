/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/10 15:37:39 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_redir_out(t_token *current_token)
{
    return (current_token->type == redir_out);
}

int is_append(t_token *current_token)
{
    return (current_token->type == append);
}

int find_number_of_outfiles(t_token *start)
{
	int number_of_outfiles;
	
	number_of_outfiles = 0;
	while (!is_eof(start) && !is_pipe(start))
	{
		if (is_redir_out(start) || is_append(start))
		{
			start = start->next;
			if (access(start->value, F_OK) && !access(start->value, W_OK))
			{
				ft_printf(2, "minishell: %s: Permission denied\n", start->value);
				return(number_of_outfiles);				
			}
			else 
				number_of_outfiles++;			
		}
		start = start->next;
	}
	return (number_of_outfiles);
}

void    find_outfiles(t_proc_struct *proc_struct, t_token *start)
{
	t_token *previous_token;
	int number_of_outfiles;
	int i;
	
	i = 0;
	number_of_outfiles = find_number_of_outfiles(start);
	proc_struct->outfiles = malloc((number_of_outfiles + 1) * sizeof(int *));
	if (number_of_outfiles)
	while (!is_eof(start) && !is_pipe(start)) /////////////// this might be a problem. 
	{
		if ((is_redir_out(start) || is_append(start)))
		{
			start = start->next;
			(proc_struct->outfiles)[i] = malloc(sizeof(int *));
			if (is_redir_out(start->previous))
				*((proc_struct->outfiles)[i]) = open(start->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else if (is_append(start->previous))
				*((proc_struct->outfiles)[i]) = open(start->value, O_CREAT | O_APPEND | O_WRONLY, 0644);             
			i++;
		}   
		start = start->next;
	}
	(proc_struct->outfiles)[number_of_outfiles] = NULL;
	return;   
}