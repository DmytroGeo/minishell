/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles_and_outfiles.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:12:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/13 13:27:33 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	init_outfile(int i, t_token *start, t_proc *proc)
{
	char	*file_name;
	int		fd;

	fd = 0;
	file_name = ((t_tok_cont *)(start->content))->value;
	if (is_redir_out(start->previous))
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (is_append(start->previous))
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	(proc->outfiles)[i] = fd;
	return (0);
}

int	init_infile(int i, t_token *start, t_proc *proc)
{
	char	*file_name;
	int		fd;

	file_name = ((t_tok_cont *)(start->content))->value;
	if (is_redir_in(start->previous))
	{
		fd = open(file_name, O_RDONLY);
		(proc->infiles)[i] = fd;
	}
	else if (is_heredoc(start->previous))
	{
		fd = heredoc_fd(file_name);
		if (fd == -42)
			return (-42);
		else
			(proc->infiles)[i] = fd;
	}
	return (0);
}

int	find_infiles(t_proc *proc, t_token *start)
{
	int	i;

	i = 0;
	if (proc->num_inf == 0)
		return (0);
	while (i < proc->num_inf)
	{
		if (is_redir_in(start) || is_heredoc(start))
		{
			start = start->next;
			if (init_infile(i, start, proc) == -42)
				return (-42);
			i++;
		}
		start = start->next;
	}
	return (0);
}

int	find_outfiles(t_proc *proc, t_token *start)
{
	int	i;

	i = 0;
	if (proc->num_outf == 0)
		return (0);
	while (i < proc->num_outf)
	{
		if ((is_redir_out(start) || is_append(start)))
		{
			start = start->next;
			init_outfile(i, start, proc);
			i++;
		}
		start = start->next;
	}
	return (0);
}

int	find_infiles_and_outfiles(t_proc *proc, t_token *start)
{
	find_num_inf_and_outf(proc, start);
	if (proc->num_inf == 0 && proc->num_outf == 0)
		return (0);
	if (proc->num_inf != 0)
	{
		proc->infiles = ft_calloc(proc->num_inf, sizeof(int));
		if (!(proc->infiles))
			return (-42);
		if (find_infiles(proc, start) < 0)
			return (-42);
	}
	if (proc->num_outf != 0)
	{
		proc->outfiles = ft_calloc(proc->num_outf, sizeof(int));
		if (!(proc->outfiles))
			return (-42);
		if (find_outfiles(proc, start) < 0)
			return (-42);
	}
	return (0);
}
