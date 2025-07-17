/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:01:40 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 12:52:42 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

void	free_proc_contents(t_proc *proc)
{
	if (!proc)
		return ;
	if (proc->infiles)
		free(proc->infiles);
	if (proc->outfiles)
		free(proc->outfiles);
	if (proc->cmd_and_args)
		ft_array_free((void **)proc->cmd_and_args);
	return ;
}

void free_proc_array(t_proc *proc_array, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free_proc_contents(&(proc_array[i]));
		i++;
	}
	free(proc_array);
	return ;
}

void	free_main(t_main *main)
{
	if (main->prompt)
		free (main->prompt);
	if (main->envp)
		ft_array_free((void **)main->envp);
	if (main->proc_array)
		free_proc_array(main->proc_array, main->num_of_proc);
	if (main->token_chain)
		free_tok_chain(&(main->token_chain), del_tok_cont);
	return;
}

