/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:54:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/18 13:31:27 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "../parsing/parsing.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>
# include <linux/limits.h>

int		execute_built_ins(t_cshell *cshell, int i);
int     ft_chdir(char **new_directory, char **prompt, char ***envp);
int     execution(t_cshell *cshell);
int		wait_for_processes(int *pid, int ac);
int     export_all_variables(char **arguments, char ***envp);
int     unset_all_variables(char **arguments, char ***envp);
int     ft_echo(int fd, char **arguments);
int     print_envp(int fd, char **envp);
int		ft_exit(char **cmd_and_args, t_cshell *cshell);
int		execute_in_main(t_cshell *cshell);

void	close_fds(int **fd, int len);
void	ft_perror(char *str, char c);
void	process_loop(t_cshell *cshell);
void	execute(int i, t_cshell *cshell);
void	free_and_exit(int *pid, int **fd, t_cshell *cshell);
void	dup_infile(int i, t_cshell *cshell);
void	dup_outfile(int i, t_cshell *cshell);
void	init_setup(t_cshell *cshell);
void	evaluate_and_execute(t_cshell *cshell, int *exit_code);
#endif