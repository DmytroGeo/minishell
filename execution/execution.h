/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:54:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:32:40 by dgeorgiy         ###   ########.fr       */
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

int		execute_built_ins(t_simple_command *simple_command, char *full_command, int *pid, int **fd);
int     change_directory(char **new_directory, char **prompt, char ***envp);
int		proc_call(int i, char c);
int     execution(t_simple_command *simple_command);
int		wait_for_processes(int *pid, int ac);
int     free_simple_command(t_simple_command *simple_command);
int     export_all_variables(char **arguments, char ***envp);
int     unset_all_variables(char **arguments, char ***envp);
int		check_built_ins(t_simple_command *simple_command);
int     ft_echo(int fd, char **arguments);
int     print_envp(int fd, char **envp);
int     ft_exit(char **commands_and_arguments, int *pid, int **fd, t_simple_command *simple_command);

void	close_fds(int **fd, int len);
void	init_setup(int **pid, int ***fd, t_simple_command *simple_command);
void	dup_infile(int **fd, int *pid, t_simple_command *simple_command);
void	dup_outfile(int **fd, int *pid, t_simple_command *simple_command);
void	ft_perror(char *str, char c);
void	process_loop(int *pid, int **fd, t_simple_command *simple_command);
void	execute(char *command_to_be_executed, int **fd, int *pid, t_simple_command *simple_command);
void	free_and_exit(int *pid, int **fd, t_simple_command *simple_command);
#endif