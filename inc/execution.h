/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:06:27 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/27 19:45:55 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "structures.h"

int			execute_built_ins(t_cshell *cshell, int i, int outfile_fd);
int			ft_chdir(char **new_directory, char **prompt, char ***envp);
int			execution(t_cshell *cshell);
int			wait_for_processes(int *pid, int ac);
int			unset_all_vars(char **arguments, char ***envp);
int			ft_echo(int fd, char **arguments);
int			print_envp(int fd, char **envp);
int			ft_exit(char **cmd_and_args, t_cshell *cshell);
int			execute_in_main(t_cshell *cshell);
int			export_all_vars(char **arguments, char ***envp, int fd);
int			is_valid_var_unset(char *str);
int			export_variable(char ***envp, char *assignment);
int			is_valid_variable_assignment(char *str);
int			find_envp_index(char **envp, const char *key);

void		proc_call(int i, char c);
void		close_fds(int **fd, int len);
void		process_loop(t_cshell *cshell);
void		execute_in_child(int i, t_cshell *cshell);
void		free_and_exit(int *pid, int **fd, t_cshell *cshell);
void		dup_infile(int i, t_cshell *cshell);
void		dup_outfile(int i, t_cshell *cshell);
void		init_setup(t_cshell *cshell);
void		evaluate_and_execute(t_cshell *cshell, int *exit_code);
void		ft_pwd(int outfile_fd);

#endif