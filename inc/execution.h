/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:06:27 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/08 16:17:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "structures.h"

int			is_valid_var_unset(char *str);
int			export_variable(char ***envp, char *assignment);
int			is_valid_variable_assignment(char *str);
int			find_envp_index(char **envp, const char *key);

void		execute_in_main(t_cshell *cshell);
void		export_all_vars(char **arguments, t_cshell *cshell, int fd);
void		unset_all_vars(char **arguments, t_cshell *cshell);
void		ft_echo(int fd, char **arguments, t_cshell *cshell);
void		print_envp(int fd, char **envp);
void		ft_exit(char **cmd_and_args, t_cshell *cshell);
void		execute_built_ins(t_cshell *cshell, int i, int outfile_fd);
void		ft_chdir(char **new_directory, t_cshell *cshell);
void		execution(t_cshell *cshell);
void		close_pipes(int **fd, int len);
void		process_loop(t_cshell *cshell);
void		execute_in_child(int i, t_cshell *cshell);
void		free_and_exit(int *pid, int **fd, t_cshell *cshell);
void		do_redirections(int i, t_cshell *cshell);
void		initialise_pipes(t_cshell *cshell);
void		evaluate_and_execute(t_cshell *cshell);
void		ft_pwd(int outfile_fd);
void		wait_for_processes(t_cshell *cshell);
void		exit_with_code(t_cshell *cshell, int i);

#endif