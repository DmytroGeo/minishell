/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:30:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/27 11:25:10 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "lexing.h"
#include "libft.h"
#include "parsing.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>


char	*get_cwd(void);
char	*get_prompt(void);
void    change_directory(char *new_directory, char **prompt);
int		evaluate_built_ins(t_token *token_chain, int *exit_status, char **prompt);

#endif