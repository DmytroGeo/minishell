/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:54:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/25 15:03:41 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
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

typedef struct s_execution_content
{
	int				number_of_commands;
	int				index;
	char			*path;
	char			**flags;
	char			**envp;	
} t_execution_content;

void	close_fds(int **fd, int len);
int		proc_call(int i, char c);
char	*get_path(char *str, char **envp);
char	**get_flags(char **arr);
void	init_list(int number_of_commands, char **commands, char **envp, t_list **head);
void	init_setup(int **pid, int ***fd, t_simple_command *simple_command, t_list **head);
int		proc_call(int i, char c);
int		execution(int number_of_commands, t_simple_command *simple_command, char **envp);
void	execute(int i, int **fd, int *pid, t_list **head);
int		wait_for_processes(int *pid, int ac);
void	dup_infile(int **fd, int *pid, t_list **head, t_simple_command *simple_command);
void	dup_outfile(int **fd, int *pid, t_list **head, t_simple_command *simple_command);
void	free_and_exit(int *pid, int **fd, t_list **head);
void	ft_free_paths_and_flags(void *content);
void	ft_perror(char *str, char c);
void	ft_intarr_free(int **fd, int len);
int	heredoc(char *limiter);
void	process_loop(t_list **head, int *pid, int **fd, t_simple_command *simple_command);

t_list	*ft_find_node(int i, t_list **head);
t_execution_content *ft_init_content(char *pa, char **fl, int ac, char **envp);

#endif