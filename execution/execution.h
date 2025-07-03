/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:54:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/02 17:30:38 by dgeorgiy         ###   ########.fr       */
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

typedef struct s_execution_content
{
	int				number_of_commands;
	int				index;
	char			*command_name;
	// char			**address_of_prompt;
	char			*path;
	char			**flags;
	char			**envp;	
} t_execution_content;

void	close_fds(int **fd, int len);
int		proc_call(int i, char c);
char	**get_flags(char **arr);
void	init_list(t_simple_command *simple_command, char **commands, char **envp, t_list **head);
void	init_setup(int **pid, int ***fd, t_simple_command *simple_command, t_list **head);
int		proc_call(int i, char c);
int		execution(t_simple_command *simple_command, char ***envp, char **address_of_prompt);
void	execute(int i, int **fd, int *pid, t_list **head);
int		wait_for_processes(int *pid, int ac);
void	dup_infile(int **fd, int *pid, t_list **head, t_simple_command *simple_command);
void	dup_outfile(int **fd, int *pid, t_list **head, t_simple_command *simple_command);
void	free_and_exit(int *pid, int **fd, t_list **head);
void	ft_free_paths_and_flags(void *content);
void	ft_perror(char *str, char c);
void	ft_intarr_free(int **fd, int len);
int		heredoc(char *limiter);
void	process_loop(t_list **head, int *pid, int **fd, t_simple_command *simple_command);
void	execute_built_ins_in_child(char *command_name, char **arguments, t_list *head);
void    change_directory(char **new_directory, char **prompt, char **envp);
void	export_all_variables(char **arguments, char ***envp);
void	unset_all_variables(char **arguments, char ***envp);
int		check_built_ins(t_simple_command *simple_command);
void	ft_echo(int fd, char **arguments);
int		execute_built_ins(char *full_command, int outfile_fd, char ***envp, char **prompt);
void	execute_built_ins_in_main(t_simple_command *simple_command, char ***envp, char **prompt);

t_list	*ft_find_node(int i, t_list **head);
t_execution_content *ft_init_content(char *pa, char **fl, int ac, char **envp);

#endif