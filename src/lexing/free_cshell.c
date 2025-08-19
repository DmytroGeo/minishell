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
#include "minishell.h"

void	free_proc_contents(t_proc *proc)
{
	if (!proc)
		return ;
	if (proc->num_inf > 0 && (proc->infiles)[proc->num_inf - 1] > 0)
		close((proc->infiles)[proc->num_inf - 1]);
	free(proc->infiles);
	if (proc->num_outf > 0 && (proc->outfiles)[proc->num_outf - 1] > 0)
		close((proc->outfiles)[proc->num_outf - 1]);
	free(proc->outfiles);
	ft_array_free((void **)(proc->cmd_and_args));
	return ;
}

void	free_proc_array(t_proc *proc_array, int len)
{
	int	i;

	i = 0;
	if (!proc_array)
		return ;
	while (i < len)
	{
		free_proc_contents(&(proc_array[i]));
		i++;
	}
	free(proc_array);
	return ;
}

void	delete_heredoc_files(int num_heredocs)
{
	int		i;
	char	*temp;
	char	*file_name;
	char	*number;

	i = 0;
	while (i < num_heredocs)
	{
		number = ft_itoa(i);
		file_name = ft_strjoin(".heredoc", number);
		free(number);
		temp = file_name;
		file_name = ft_strjoin(temp, ".tmp");
		free(temp);
		if (unlink(file_name) == -1)
			exit (-42);
		free(file_name);
		i++;
	}
}

/**
 * @param cshell The address of 'cshell' structure.
 * @return Nothing (void function).
 * @brief This function frees pid, fd, proc_array and tok_chain.
 */
void	free_cshell(t_cshell *cshell)
{
	free(cshell->line_read);
	cshell->line_read = NULL;
	free(cshell->pid);
	cshell->pid = NULL;
	ft_array_free2((void **)(cshell->fd), cshell->num_of_proc - 1);
	cshell->fd = NULL;
	free_proc_array(cshell->proc_array, cshell->num_of_proc);
	cshell->proc_array = NULL;
	free_tok_chain(&(cshell->token_chain), del_tok_cont);
	cshell->token_chain = NULL;
	delete_heredoc_files(cshell->num_heredocs);
	cshell->num_heredocs = 0;
	return ;
}

/**
 * @param cshell The address of 'cshell' structure.
 * @return Nothing (void function).
 * @brief This function frees the prompt, envp,
 * and then runs free_cshell().
 */
void	free_whole_cshell(t_cshell *cshell)
{
	free(cshell->prompt);
	cshell->prompt = NULL;
	ft_array_free((void **)(cshell->envp));
	cshell->envp = NULL;
	free_cshell(cshell);
	return ;
}
