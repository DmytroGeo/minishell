/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:30:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 12:55:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>

typedef struct s_exit_codes
{
    int cshell_exit_code;
    int lexing_exit_code;
    int parsing_exit_code;
} t_exit_codes;

#endif