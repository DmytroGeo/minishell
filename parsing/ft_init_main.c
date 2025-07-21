/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:10:27 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 12:10:48 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_cshell(t_cshell *cshell, char **envp)
{
	cshell->envp = copy_envp(envp);
	cshell->prompt = get_prompt();
	cshell->pid = NULL;
	cshell->fd = NULL;
	cshell->proc_array = NULL;
	cshell->token_chain = NULL;
	return ;
}
