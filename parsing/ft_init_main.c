/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:53:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 14:19:32 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void	init_main(t_main *main, char **envp)
{
	main->envp = copy_envp(envp); // creates a coy of envp
	main->prompt = get_prompt(); // creates a copy of the prompt
	main->proc_array = NULL;
	main->token_chain = NULL;
	return ;
}