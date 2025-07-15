/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_envp_and_prompt.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:53:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 16:57:39 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void	init_envp_and_prompt(t_main *main, char **envp)
{
	main->envp = copy_envp(envp);
	main->prompt = get_prompt();
	main->proc_array = NULL;
}