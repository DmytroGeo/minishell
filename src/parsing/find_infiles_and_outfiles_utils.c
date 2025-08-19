/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles_and_outfiles_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:15:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/13 13:27:58 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	check_inf_or_outf(t_token *start, char *file_name, t_proc *proc)
{
	if (is_heredoc(start) || is_redir_in(start))
	{
		proc->num_inf++;
		if (is_redir_in(start) && access(file_name, F_OK) != 0)
			return (exist_err(file_name), 1);
		else if (is_redir_in(start) && access(file_name, R_OK) != 0)
			return (perm_error(file_name), 1);
	}
	else if (is_redir_out(start) || is_append(start))
	{
		proc->num_outf++;
		if (access(file_name, F_OK) == 0 && access(file_name, W_OK) != 0)
			return (perm_error(file_name), 1);
	}
	return (0);
}

void	find_num_inf_and_outf(t_proc *proc, t_token *start)
{
	char	*file_name;

	proc->num_inf = 0;
	proc->num_outf = 0;
	while (start && !is_pipe(start))
	{
		if (is_redirect(start))
		{
			start = start->next;
			file_name = ((t_tok_cont *)(start->content))->value;
			if (check_inf_or_outf(start->previous, file_name, proc) == 1)
				break ;
		}
		start = start->next;
	}
	return ;
}
