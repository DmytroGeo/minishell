/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:54:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 14:13:52 by dgeorgiy         ###   ########.fr       */
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

void	close_fds(int **fd, int len);
int		proc_call(int i, char c);
void	init_list(t_simple_command *simple_command, char **commands, char **envp);
int		proc_call(int i, char c);
int		execution(t_simple_command *simple_command, char ***envp, char **address_of_prompt);
void	init_setup(int **pid, int ***fd, t_simple_command *simple_command);
int		wait_for_processes(int *pid, int ac);
void	dup_infile(int **fd, int *pid, t_simple_command *simple_command);
void	dup_outfile(int **fd, int *pid, t_simple_command *simple_command);
void	free_and_exit(int *pid, int **fd, t_simple_command *simple_command);
void	ft_perror(char *str, char c);
void	ft_intarr_free(int **fd, int len);
void	export_all_variables(char **arguments, char ***envp);
void	process_loop(int *pid, int **fd, t_simple_command *simple_command);
void	execute_built_ins_in_child(char *command_name, char **arguments);
void    change_directory(char **new_directory, char **prompt, char **envp);
void	export_all_variables(char **arguments, char ***envp);
void	unset_all_variables(char **arguments, char ***envp);
int		check_built_ins(t_simple_command *simple_command);
void	ft_echo(int fd, char **arguments);
void	execute_built_ins_in_main(t_simple_command *simple_command, char ***envp, char **prompt);
void	print_env(int fd, char **envp);
void	execute(int i, int **fd, int *pid, char **envp, t_simple_command *simple_command);
void	free_simple_command(t_simple_command *simple_command);
int		execute_built_ins(t_simple_command *simple_command, char ***envp, char **prompt, char *full_command);
#endif