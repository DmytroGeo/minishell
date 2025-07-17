/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:54:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/17 18:01:50 by dgeorgiy         ###   ########.fr       */
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

int		execute_built_ins(t_main *main, int i, int *pid, int **fd);
int     ft_chdir(char **new_directory, char **prompt, char ***envp);
int     execution(t_main *main);
int		wait_for_processes(int *pid, int ac);
int     export_all_variables(char **arguments, char ***envp);
int     unset_all_variables(char **arguments, char ***envp);
int     ft_echo(int fd, char **arguments);
int     print_envp(int fd, char **envp);
int		ft_exit(char **cmd_and_args, int *pid, int **fd, t_main *main);
int		execute_in_main(t_main *main, int *pid, int **fd);

void	close_fds(int **fd, int len);
void	ft_perror(char *str, char c);
void	process_loop(int *pid, int **fd, t_main *main);
void	execute(int i, int **fd, int *pid, t_main *main);
void	free_and_exit(int *pid, int **fd, t_main *main);
void	dup_infile(int i, int **fd, int *pid, t_main *main);
void	dup_outfile(int i, int **fd, int *pid, t_main *main);
void	init_setup(int **pid, int ***fd, t_main *main);
int     evaluate_and_execute(t_main *main, int exit_code);
#endif