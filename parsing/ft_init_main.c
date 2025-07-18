/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:53:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 14:19:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void	init_cshell(t_cshell *cshell, char **envp)
{
	cshell->envp = copy_envp(envp); // creates a coy of envp
	cshell->prompt = get_prompt(); // creates a copy of the prompt
	cshell->pid = NULL;
	cshell->fd = NULL;
	cshell->proc_array = NULL;
	cshell->token_chain = NULL;
	return ;
}