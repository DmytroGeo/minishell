/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:43:50 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/12 17:34:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structures.h"

void		free_whole_cshell(t_cshell *cshell);
void		free_cshell(t_cshell *cshell);
void		free_proc_array(t_proc *proc_array, int len);
void		del_tok_cont(void *content);
void		free_tok_chain(t_token **start, void (*del)(void*));
void		perm_error(char *file_name);
void		exist_err(char *file_name);

char		*get_path(char *str, char **envp);
char		*find_var_in_envp(char **envp, char *variable);

int			get_prompt(char **address_of_prompt);

#endif