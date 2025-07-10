/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp_and_prompt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:20:20 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/10 13:23:52 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		init_envp_and_prompt(t_big_struct *big_struct, char **envp)
{
    char **my_envp;

    big_struct->prompt = get_prompt();
    my_envp = copy_envp(envp);
    big_struct->envp = my_envp;
}