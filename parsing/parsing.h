/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:21:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/27 15:52:04 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "libft.h"
#include "lexing.h"

// typedef struct s_tree
// {
//     t_simple_command *command;
// }           t_tree;

t_simple_command  *parse(t_token *token_chain);

int is_EOF(t_token *current_token);
// int	heredoc(char *end_of_file);
void	copy_envp(char ***envp);
int	is_export(t_token *token);
int	is_valid_variable_name(char *str);
void	export_variable(char ***envp, const char *assignment);
int is_valid_variable_assignment(char *str);
void	unset_variable(char ***envp, const char *key);
int	find_env_index(char **envp, const char *key);
void print_env(char **envp);
void	ft_print_envp(char **envp);

#endif